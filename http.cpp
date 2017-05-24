//
// Created by joseph on 5/23/17.
//

#include "http.h"

Http::Http() {}


void Http::sendScore(int score, std::string name) {
    // prepare the request
    sf::Http::Request request("/v2/59251a5b2b0000f706e81bac", sf::Http::Request::Get);

    // encode the parameters in the request body
    //std::string stream = std::string("name=") + name + std::string("&score=") + std::to_string(score);
    //request.setBody(stream);

    // send the request
    sf::Http http("http://www.mocky.io/");
    sf::Http::Response response = http.sendRequest(request);

    // check the status
    if (response.getStatus() == sf::Http::Response::Ok) {
        // check the contents of the response
        std::cout << response.getBody() << std::endl;
        parseJson(response.getBody());
    } else {
        std::cerr << "HTTP error " << response.getStatus() << std::endl;
        std::cerr << "request failed" << std::endl;
    }
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
    std::cout << "Nuevo objeto" << std::endl;
    for (picojson::value::object::const_iterator i = obj.begin(); i != obj.end(); ++i) {
        std::cout << "Llave: " << i->first << std::endl;
        std::cout << "Valor: ";
        checkValue(i->second);

        std::cout << std::endl;
    }
}


void Http::parseJsonArray(const picojson::array &arr) {
    std::cout << "(ES ARRAY)";
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
        std::cout << value.to_str();
    }
}
