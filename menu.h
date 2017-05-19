//
// Created by jimena on 18/05/17.
//

#ifndef GENETICCOLOSSEUM_MENU_H
#define GENETICCOLOSSEUM_MENU_H

#include <SFML/Graphics.hpp>
#include "screen.h"
#include "string"


class menu : public screen{
public:
    menu();
    int run(sf::RenderWindow &window);
};

#endif //GENETICCOLOSSEUM_MENU_H
