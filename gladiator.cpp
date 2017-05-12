#include "gladiator.h"

Gladiator::Gladiator()
{

}

Gladiator::Gladiator(DNA dna)
{
    setDna(dna);
}

bool Gladiator::defend(int damage)
{
    life-=damage-damage*(0.6*shield/100);
    return !isAlive();

}

void Gladiator::attack()
{
    if(attackClock.getElapsedTime().asMilliseconds() > ATTACK_WAIT_TIME){
        std::vector<Gladiator> closest = getClosest( ATTACK_RADIUS,1);
        if(closest.size()){
            attack(&closest[0]);
            attackClock.restart();
        }
    }
}

void Gladiator::calcVariables()
{
     setSpeed(MAXSPEED-MAXSPEED*0.6*(dna.genes[Weight]/100.f));
     //std::cout<<" weight"<<dna.genes[Weight]<<"\n";
     setDamage(dna.genes[Attack]+dna.genes[Attack]*(0.3*dna.genes[Weight]/100.f));
     setShield(dna.genes[Shield]+dna.genes[Shield]*(0.3*dna.genes[Weight]/100.f));

}

void Gladiator::increaseFitness(int value)
{
 dna.setFitness(dna.getFitness()+value);
}

float Gladiator::getDamage() const
{
    return damage;
}

void Gladiator::setDamage(float value)
{
    damage = value;
}

void Gladiator::attack(Gladiator *enemy)
{
    if( enemy->defend( getDamage() ) ){
        increaseFitness(5);
    }
}

void Gladiator::update()
{
    //std::cout<<" asdasd" <<"\n";

    //std::cout<< getSpeed() <<"\n";
    sprite.move(getSpeed(), dna.genes[VericalCost]/50.f*Xspeed);
}

DNA Gladiator::getDna() const
{
    return dna;
}

void Gladiator::setDna(const DNA &value)
{
    dna = value;
    calcVariables();
}

bool Gladiator::isAlive()
{
    return life>0;
}

void Gladiator::testCalcFitness(sf::Vector2f value)
{
    dna.setFitness(pow(2000-calcDistance(value),2));
}

float Gladiator::getShield() const
{
    return shield;
}

void Gladiator::setShield(float value)
{
    shield = value;
}

std::vector<Gladiator> Gladiator::getClosest(float radius, int amount)
{
    std::vector<Gladiator> closest(gladiatorsList->begin(),gladiatorsList->end());
    sortByDistance(&closest);
    if(amount>closest.size()){
        amount=closest.size();
    }
    return std::vector<Gladiator>(closest.begin(),closest.begin()+amount);
}

float Gladiator::getSpeed() const
{
    return speed;
}

void Gladiator::setSpeed(float value)
{
    speed = value;
}


float Gladiator::calcDistance(sf::Vector2f pos){
    sf::Vector2f distance;
    distance.x = sprite.getPosition().x - pos.x;
    distance.y = sprite.getPosition().y - pos.y;
    //float distance = 0;
    return  sqrt(pow(distance.x, 2) + pow(distance.y, 2));

}


void Gladiator::sortByDistance(std::vector<Gladiator> *list){
    sortByDistance( list, 0, gladiatorsList->size()-1);
}

void Gladiator::sortByDistance(std::vector<Gladiator> *list, int left, int right)
{
    int i = left, j = right;
    Gladiator tmp;
    //int pivot = list->operator []((left + right) / 2).getFitness();
    float pivot = calcDistance(list->operator[]((left + right) / 2).getPosition());
    /* partition */
    while (i <= j) {
        //while (list->operator [](i).getFitness() < pivot)
        while ( calcDistance(list->operator [](i).getPosition()) < pivot)
            i++;
        //while (list->operator [](j).getFitness() > pivot)
        while (calcDistance(list->operator [](j).getPosition()) > pivot)
            j--;
        if (i <= j) {
            tmp = list->operator [](i);
            list->operator [](i) = list->operator [](j);
            list->operator [](j)= tmp;
            i++;
            j--;
        }
    };
    /* recursion */
    if (left < j)
        sortByDistance(list, left, j);
    if (i < right)
        sortByDistance(list, i, right);

}
