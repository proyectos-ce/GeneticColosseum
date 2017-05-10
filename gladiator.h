#ifndef GLADIATOR_H
#define GLADIATOR_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "dna.h"
#include "entity.h"
#include <time.h>
#include <iostream>




#include <SFML/Audio.hpp>
#include <fstream>

#define MAXSPEED 4
#define ATTACK_WAIT_TIME 1000
#define DEFEND_WAIT_TIME 1000
#define ATTACK_RADIUS 50


class Gladiator : public Entity
{
public:
    Gladiator();
    Gladiator(DNA dna);

    bool defend(int damage);
    void attack();
    void attack(Gladiator *enemy);
    DNA dna;

    //sf::Vector2f getPosition();
    //void draw();
    void update();
    bool isAlive();
    void testCalcFitness(sf::Vector2f value);





    DNA getDna() const;
    void setDna(const DNA &value);

private:
    sf::Clock attackClock;
    sf::Clock defendClock;
    float life = 1000;
    float speed = 0;
    float damage = 0;
    float shield = 0;
    void calcVariables();
    void increaseFitness(int value);
    //sf::Sprite sprite;
    std::vector<Gladiator> *gladiatorsList;
    std::vector<Gladiator> *enemyList;//cambiar a tipo enemigo o trampa
    float getSpeed() const;
    void setSpeed(float value);
    float getDamage() const;
    void setDamage(float value);
    float getShield() const;
    void setShield(float value);
    std::vector<Gladiator> getClosest(float radius = 50, int amount = 0);
    float calcDistance(sf::Vector2f pos);
    void sortByDistance(std::vector<Gladiator> *list);
    void sortByDistance(std::vector<Gladiator> *list, int left, int right);
};



#endif // GLADIATOR_H
