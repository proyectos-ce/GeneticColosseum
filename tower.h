#ifndef TOWER_H
#define TOWER_H

#include <SFML/Graphics.hpp>
#include "gladiator.h"

class Tower
{
public:
    Tower();
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Clock attackClock;
    int pos_x;
    int pos_y;
    void set_place(int x, int y);
    void update(sf::RenderWindow &window);
    void attack(Gladiator *gladiator);
    float calcDistance(sf::Vector2f pos);
    sf::Vector2f getPosition();

    std::vector<Gladiator* > getClosest(float radius, std::vector<Gladiator> *gladiatorsList);


private:

};

#endif // TOWER_H
