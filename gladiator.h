#ifndef GLADIATOR_H
#define GLADIATOR_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "dna.h"
#include "entity.h"
#include <time.h>
#include <iostream>
#include <list>



#include <SFML/Audio.hpp>
#include <fstream>
#define Xspeed 2
#define MAXSPEED 4*Xspeed
#define ATTACK_WAIT_TIME 500
#define DEFEND_WAIT_TIME 500
#define ATTACK_RADIUS 10
#define NEAR_TRIGGER_RADIUS 200


class Gladiator : public Entity
{
public:
    Gladiator();
    Gladiator(DNA dna);
    DNA dna;



    void update();
    bool isAlive();
    void testCalcFitness(sf::Vector2f value);

    DNA getDna() const;
    void setDna(const DNA &value);

    std::list<sf::Vector2f> getLabyrinthDirections() const;
    void setLabyrinthDirections(const std::list<sf::Vector2f> &value);

    std::vector<Gladiator> *getGladiatorsList() const;
    void setGladiatorsList(std::vector<Gladiator> *value);

    sf::FloatRect getBorders() const;
    void setBorders(const sf::FloatRect &value);

    float getLife() const;
    void setLife(float value);
    double getFitness();
    int getKills() const;
    void setKills(int value);

private:
    sf::Clock attackClock;
    sf::Clock defendClock;
    float life = 100;
    float speed = 0;
    float damage = 0;
    float shield = 0;
    bool fighting = false;
    bool runningAway = false;
    int kills=0;
    sf::Vector2f shovePos;
    std::list<sf::Vector2f> labyrinthDirections;
    bool move(sf::Vector2f movement, bool checkBorders = false);
    bool defend(int damage);
    bool defend(int damage, sf::Vector2f attackerPos);
    void attack(Gladiator *closest);
    bool moveTo(sf::Vector2f pos, bool checkBorders= false, float speedMultiplier=1); // verdadero si ha llegado
    sf::FloatRect borders;
    void calcVariables();
    void increaseFitness(int value);
    //sf::Sprite sprite;
    std::vector<Gladiator> *gladiatorsList;
    //std::vector<Gladiator> *enemyList;//cambiar a tipo enemigo o trampa
    float getSpeed() const;
    void setSpeed(float value);

    float getDamage() const;
    void setDamage(float value);

    float getShield() const;
    void setShield(float value);
    bool hasClosest(float radius = 50, int amount = 0);
    std::vector<Gladiator *> getClosest(float radius = 50, int amount = 0);
    float calcDistance(sf::Vector2f pos);

    void sortByDistance(std::vector<Gladiator *> *list);
    void sortByDistance(std::vector<Gladiator *> *list, int left, int right);
};



#endif // GLADIATOR_H
