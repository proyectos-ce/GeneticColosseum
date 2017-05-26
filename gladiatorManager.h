//
// Created by jimena on 18/05/17.
//

#ifndef GENETICCOLOSSEUM_GLADIATORMANAGER_H
#define GENETICCOLOSSEUM_GLADIATORMANAGER_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "dna.h"
#include"populationmanager.h"
#include"gladiator.h"
#include "screen.h"


class gladiatorManager : public screen{
public:
    gladiatorManager();
    time_t t;
    sf::Texture texture;
    sf::Sprite sprite;

    sf::Texture bg1Tex;
    sf::Sprite bg1Sprite;

    std::vector<Gladiator> gladiatorList;
    Gladiator gladiator;
    sf::Texture Gtexture;


    sf::Clock cycleClock;

    std::vector<DNA> resultPop;

    PopulationManager population;

    int run(sf::RenderWindow &window);

};

#endif //GENETICCOLOSSEUM_GLADIATORMANAGER_H
