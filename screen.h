//
// Created by jimena on 18/05/17.
//

#ifndef GENETICCOLOSSEUM_SCREEN_H
#define GENETICCOLOSSEUM_SCREEN_H

#include <SFML/Graphics.hpp>

class screen{
public:
    virtual int run (sf::RenderWindow &window, std::string &ip) = 0;
};
#endif //GENETICCOLOSSEUM_SCREEN_H
