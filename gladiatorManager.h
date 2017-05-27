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
#include "tower.h"
#include "Grid.h"


class gladiatorManager : public screen{
public:
    sf::Clock roundClock;
    gladiatorManager();

    time_t t;

    sf::Texture bg1Tex;
    sf::Sprite bg1Sprite;

    std::vector<Gladiator> gladiatorList1;
    std::vector<Gladiator> gladiatorList2;
    std::vector<Gladiator> deadGladiatorList1;
    std::vector<Gladiator> deadGladiatorList2;
    std::vector<Tower> towerlist_izq;
    std::vector<Tower> towerlist_der;
    std::vector<DNA> dnaList1;
    std::vector<DNA> dnaList2;
    Gladiator gladiator;
    sf::Texture Gtexture1;
    sf::Texture Gtexture2;
    sf::FloatRect borders;
    void extractDNA();
    sf::Texture intiZoneTexture;
    sf::Texture coliseumTexture;
    sf::Texture trunkTexture;
    sf::Texture crystalTexture;
    sf::Texture holeTexture;

    sf::Sprite intiZoneSpriteL;
    sf::Sprite intiZoneSpriteR;
    sf::Sprite coliseumSprite;

    Grid* rightGrid;
    Grid* leftGrid;



    sf::Clock cycleClock;

    std::vector<DNA> resultPop;

    stats Stats = stats();

    Tower torre = Tower();

    PopulationManager population;

    std::vector<sf::Texture> texturesArray;
    std::vector<sf::Sprite> spritesArray;

    int run(sf::RenderWindow &window, std::string& ip);

    sf::FloatRect getBorders() const;
    void setBorders(const sf::FloatRect &value);
    void setObstacles(Grid* grid, sf::RenderWindow &window);
    void drawObstacles(sf::RenderWindow &window);
};

#endif //GENETICCOLOSSEUM_GLADIATORMANAGER_H
