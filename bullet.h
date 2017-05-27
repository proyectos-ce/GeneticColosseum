//
// Created by danielc on 27/05/17.
//

#ifndef GENETICCOLOSSEUM_BULLET_H
#define GENETICCOLOSSEUM_BULLET_H


#include <SFML/Graphics.hpp>

class bullet {
public:
    bullet();
    sf::Sprite sprite;
    sf::Texture texture;
    void update(sf::RenderWindow &window);

};


#endif //GENETICCOLOSSEUM_BULLET_H
