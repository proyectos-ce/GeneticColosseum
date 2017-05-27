//
// Created by joseph on 5/23/17.
//

#ifndef GENETICCOLOSSEUM_HTTP_H
#define GENETICCOLOSSEUM_HTTP_H


#include <SFML/Network.hpp>
#include <sstream>
#include <iostream>
#include <functional>
#include "picojson.h"
#include "dna.h"

class Http {


    Http();

public:

    static std::string server;

    static std::vector<DNA> getNext(int population, std::vector<DNA> data);

    static std::vector<DNA> getFirst(int population);

private:

    static void parseJson(std::string json);

    static void parseJsonObject(const picojson::object &obj);

    static void parseJsonArray(const picojson::array &arr);

    static void checkValue(const picojson::value &value);

    static std::string prepareData(std::vector<DNA> data);

    static std::vector<DNA> parseDNAJson(std::string json);

    static int port;
};


#endif //GENETICCOLOSSEUM_HTTP_H
