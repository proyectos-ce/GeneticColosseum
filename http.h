//
// Created by joseph on 5/23/17.
//

#ifndef GENETICCOLOSSEUM_HTTP_H
#define GENETICCOLOSSEUM_HTTP_H


#include <SFML/Network.hpp>
#include <sstream>
#include <iostream>
#include "picojson.h"

class Http {


    Http();

public:
    static void sendScore(int score, std::string name);

    static void parseJson(std::string json);

    static void parseJsonObject(const picojson::object &obj);

    static void parseJsonArray(const picojson::array &arr);

    static void checkValue(const picojson::value &value);
};


#endif //GENETICCOLOSSEUM_HTTP_H
