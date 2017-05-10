#ifndef GLADIATOR_H
#define GLADIATOR_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "dna.h"
class Gladiator
{
public:
    Gladiator();
    bool defend(int damage);
    float attack();
    DNA genes;

    sf::Vector2f getPosition();
    void draw();
    void update();
    bool isAlive();

private:
    float life = 1000;
    float speed = 0;
    void calcSpeed();
    sf::Sprite sprite;
    std::vector<Gladiator> *gladiatorsList;
    std::vector<Gladiator> *enemyList;//cambiar a tipo enemigo o trampa


    float getSpeed() const;
    void setSpeed(float value);

};


namespace BattleUtils {
    std::vector<Gladiator> getClosest(std::vector<Gladiator> *gladiatorsList, float radius = 50, int amount = 0);

}

#endif // GLADIATOR_H
