//
// Created by joseph on 5/23/17.
//

#include "http.h"

Http::Http() {}


std::string Http::server;
int Http::port = 80;


std::string Http::prepareData(std::vector<DNA> data) {
    std::string result = "[";

    bool comma = false;
    for (std::vector<DNA>::iterator it = data.begin(); it != data.end(); ++it) {
        if (comma)
            result += ", ";

        result += "{ \"genes\": [";

        bool subcomma = false;
        for (auto &&gen: it->genes) {
            if (subcomma)
                result += ", ";

            result += std::to_string(gen);

            subcomma = true;
        }

        result += "], \"probability\": " + std::to_string(it->getProbability()) + ", \"fitness\": " +
                  std::to_string(it->getFitness()) + ", \"hash\": \"" + it->getNameHASH() + "\"}";

        comma = true;
    }

    result += "]";
    return result;
}


std::vector<DNA> Http::getFirst(int population) {
    // prepare the request
    sf::Http::Request request("/api/genetic/create/" + std::to_string(population), sf::Http::Request::Get);

    // send the request
    sf::Http http(server, port);
    sf::Http::Response response = http.sendRequest(request);

    // check the status
    if (response.getStatus() == sf::Http::Response::Ok) {
        // check the contents of the response
        ////std::cout << response.getBody() << std::endl;
        return parseDNAJson(response.getBody());
    } else {
        std::cerr << "HTTP error " << response.getStatus() << std::endl;
        std::cerr << "request failed" << std::endl;
    }
}

std::vector<DNA> Http::getNext(int population, std::vector<DNA> data) {
    // prepare the request
    sf::Http::Request request("/api/genetic/update/" + std::to_string(population), sf::Http::Request::Post);

    // encode the parameters in the request body
    std::string stream = prepareData(data);
    request.setBody(stream);
    ////std::cout << stream << std::endl;
    request.setField("Content-Type", "application/json");

    // send the request
    sf::Http http(server, port);
    sf::Http::Response response = http.sendRequest(request);

    // check the status
    if (response.getStatus() == sf::Http::Response::Ok) {
        // check the contents of the response
        //std::cout << response.getBody() << std::endl;
        return parseDNAJson(response.getBody());
    } else {
        std::cerr << "HTTP error " << response.getStatus() << std::endl;
        std::cerr << "request failed" << std::endl;
    }
}


std::vector<DNA> Http::parseDNAJson(std::string json) {
    picojson::value v;

    std::vector<DNA> result;

    std::string err = picojson::parse(v, json);

    if (!err.empty()) {
        std::cerr << err << std::endl;
        exit(1);
    }

    if (!v.is<picojson::array>()) {
        std::cerr << "El JSON es inválido, deberia ser una lista pero no lo es" << std::endl;
        exit(EXIT_FAILURE);
    }


    picojson::array &arr = v.get<picojson::array>();


    for (picojson::value::array::const_iterator i = arr.begin(); i != arr.end(); ++i) {
        if (!i->is<picojson::object>()) {
            std::cerr << "Se encontró una objeto anidado inváliado" << std::endl;
            exit(EXIT_FAILURE);
        }

        DNA *temp = new DNA();

        const picojson::value &val = i->get("genes");

        const picojson::array &subarr = val.get<picojson::array>();

        const picojson::value &prob = i->get("probability");

        const picojson::value &fit = i->get("fitness");

        const picojson::value &hash = i->get("hash");

        temp->setProbability(prob.get<double>());

        temp->setFitness(fit.get<double>());

        temp->setNameHASH(hash.to_str());


        int contador = 0;
        for (picojson::value::array::const_iterator j = subarr.begin(); j != subarr.end(); ++j) {
            temp->genes[contador] = (int) round(j->get<double>());
            contador++;
        }


        result.push_back(*temp);


    }

    return result;


}


void Http::parseJson(std::string json) {
    picojson::value v;

    std::string err = picojson::parse(v, json);

    if (!err.empty()) {
        std::cerr << err << std::endl;
        exit(1);
    }

    // check if the type of the value is "object"
    if (!v.is<picojson::object>()) {
        std::cerr << "JSON is not an object" << std::endl;
        exit(2);
    }

    // obtain a const reference to the map, and print the contents
    parseJsonObject(v.get<picojson::object>());


}

void Http::parseJsonObject(const picojson::object &obj) {
    //std::cout << "Nuevo objeto" << std::endl;
    for (picojson::value::object::const_iterator i = obj.begin(); i != obj.end(); ++i) {
        //std::cout << "Llave: " << i->first << std::endl;
        //std::cout << "Valor: ";
        checkValue(i->second);

        //std::cout << std::endl;
    }
}


void Http::parseJsonArray(const picojson::array &arr) {
    //std::cout << "(ES ARRAY)";
    for (picojson::value::array::const_iterator i = arr.begin(); i != arr.end(); ++i) {
        checkValue(*i);
    }
}

void Http::checkValue(const picojson::value &value) {
    if (value.is<picojson::array>()) {
        parseJsonArray(value.get<picojson::array>());
    } else if (value.is<picojson::object>()) {
        parseJsonObject(value.get<picojson::object>());
    } else {
        //std::cout << value.to_str();
    }
}
