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
#include "stats.h"

#define ROUND_TIME 10
class gladiatorManager : public screen{
public:
    sf::Clock roundClock;
    gladiatorManager();
    time_t t;

    sf::Texture bg1Tex;
    sf::Sprite bg1Sprite;
    int generation=0;
    std::vector<Gladiator> gladiatorList1;
    std::vector<Gladiator> gladiatorList2;
    std::vector<Gladiator> deadGladiatorList1;
    std::vector<Gladiator> deadGladiatorList2;
    std::vector<DNA> dnaList1;
    std::vector<DNA> dnaList2;
    Gladiator gladiator;
    sf::Texture Gtexture1;
    sf::Texture Gtexture2;
    sf::FloatRect borders;
    void extractDNA();
    sf::Texture intiZoneTexture;
    sf::Texture coliseumTexture;
    sf::Sprite intiZoneSpriteL;
    sf::Sprite intiZoneSpriteR;
    sf::Sprite coliseumSprite;


    sf::Clock cycleClock;

    std::vector<DNA> resultPop;

    stats Stats = stats();

    PopulationManager population;


    int run(sf::RenderWindow &window, std::string& ip);

    sf::FloatRect getBorders() const;
    void setBorders(const sf::FloatRect &value);
};

#endif //GENETICCOLOSSEUM_GLADIATORMANAGER_H
