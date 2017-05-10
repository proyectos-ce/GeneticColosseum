#ifndef GLADIATOR_H
#define GLADIATOR_H
#include <vector>

class Gladiator
{
public:
    Gladiator();
private:
    std::vector<Gladiator > *gladiatorsList;
    std::vector<Gladiator > *enemyList;
    bool defend(int damage);
    float attack();


};

#endif // GLADIATOR_H
