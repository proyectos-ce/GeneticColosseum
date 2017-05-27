//
// Created by danielc on 26/05/17.
//

#ifndef GENETICCOLOSSEUM_STATS_H
#define GENETICCOLOSSEUM_STATS_H


#include <SFML/Graphics.hpp>
#include "gladiator.h"

class stats {
public:
    stats();
    sf::Font font;
    sf::Text Gen;
    sf::Text Time;

    sf::Text Gladiador;
    sf::Text Vida;
    sf::Text Fitness;
    sf::Text Kills;

    void update_gen_stats(sf::RenderWindow &window, int generacion, int tiempo_restante);
    void update_gladiator_stats(sf::RenderWindow &window, Gladiator &gladiator);
};


#endif //GENETICCOLOSSEUM_STATS_H
