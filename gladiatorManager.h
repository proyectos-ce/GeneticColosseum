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

    std::vector<Gladiator> gladiatorList1;
    std::vector<Gladiator> gladiatorList2;
    Gladiator gladiator;
    sf::Texture Gtexture1;
    sf::Texture Gtexture2;
    sf::FloatRect borders;

    sf::Texture intiZoneTexture;
    sf::Texture coliseumTexture;
    sf::Sprite intiZoneSpriteL;
    sf::Sprite intiZoneSpriteR;
    sf::Sprite coliseumSprite;


    sf::Clock cycleClock;

    std::vector<DNA> resultPop;


    PopulationManager population;

    int run(sf::RenderWindow &window, std::string& ip);

    sf::FloatRect getBorders() const;
    void setBorders(const sf::FloatRect &value);
};

#endif //GENETICCOLOSSEUM_GLADIATORMANAGER_H
