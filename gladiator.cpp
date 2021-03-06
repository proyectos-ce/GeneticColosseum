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
    float realDamage = damage-damage*(0.4*shield/100.f);
    life-=realDamage;
    return !isAlive();

}

bool Gladiator::defend(int damage , sf::Vector2f attackerPos)
{
    bool result = false;
    if(!(labyrinthDirections.size()>0)){
    float realDamage = damage-damage*(0.4*shield/100.f);
    sf::Vector2f shoveDirection = getPosition() - attackerPos;
    float total = sqrt(pow(shoveDirection.x, 2)+ pow(shoveDirection.y,2));
    if(total <= 0.5){
        //std::cout << "r = 0, error"<<std::endl;
        total = sqrt(pow(3, 2)+ pow(3,2));
        shoveDirection.x=3;
        shoveDirection.y=3;
    }
    shoveDirection.x=shoveDirection.x/total;
    shoveDirection.y=shoveDirection.y/total;
    shovePos.x= getPosition().x+shoveDirection.x*(speed)*20.f;
    shovePos.y= getPosition().y+shoveDirection.y*(speed)*20.f;
    runningAway=true;
    result= defend(damage);
    }
    return result;
}

void Gladiator::attack(Gladiator* closest)
{
    if(attackClock.getElapsedTime().asMilliseconds() > dna.genes[AttackWaitTime]*3){
        //std::list<Gladiator>::iterator it = closest.begin();
        if( closest->defend( getDamage()/1.5, getPosition() ) ){
            increaseFitness(5);
            kills++;
        }
        attackClock.restart();



        sf::Vector2f shoveDirection = getPosition() - closest->getPosition();
        float total = sqrt(pow(shoveDirection.x, 2)+ pow(shoveDirection.y,2));
        if(total <= 0.5){
            //std::cout << "r = 0, error"<<std::endl;
            total = sqrt(pow(3, 2)+ pow(3,2));
            shoveDirection.x=3;
            shoveDirection.y=3;
        }
        shoveDirection.x=shoveDirection.x/total;
        shoveDirection.y=shoveDirection.y/total;
        shovePos.x= getPosition().x+shoveDirection.x*(speed)*20.f;
        shovePos.y= getPosition().y+shoveDirection.y*(speed)*20.f;
        runningAway=true;

    }
}

void Gladiator::calcVariables()
{
    setSpeed(MAXSPEED-MAXSPEED*0.6*(dna.genes[Weight]/100.f));
    setDamage(dna.genes[Attack]+dna.genes[Attack]*(0.3*dna.genes[Weight]/100.f));
    setShield(dna.genes[Shield]+dna.genes[Shield]*(0.3*dna.genes[Weight]/100.f));

}

void Gladiator::increaseFitness(int value)
{
    dna.setFitness(dna.getFitness()+value);
}

std::vector<Gladiator> *Gladiator::getGladiatorsList() const
{
    return gladiatorsList;
}

void Gladiator::setGladiatorsList(std::vector<Gladiator> *value)
{
    gladiatorsList = value;
}

bool Gladiator::move(sf::Vector2f movement, bool checkBorders)
{
    bool result = false;
    if(checkBorders){
        sf::Vector2f nextPos;
        nextPos.x = sprite.getGlobalBounds().left + movement.x;
        nextPos.y = sprite.getGlobalBounds().top + movement.y;

        if(! (borders.contains(nextPos.x, nextPos.y) &&
              borders.contains(nextPos.x+ sprite.getGlobalBounds().width, nextPos.y+sprite.getGlobalBounds().height) ) ){
            movement.x=0;
            movement.y=0;
            result= true;
        }
    }
    sprite.move(movement);

    if(movement.x != 0){
        if(movement.x > 0){
            sprite.setScale(0.1,0.1);
        }
        else{
            sprite.setScale(-0.1,0.1);
        }
    }
    return result;
}

float Gladiator::getDamage() const
{
    return damage;
}

void Gladiator::setDamage(float value)
{
    damage = value;
}



bool Gladiator::moveTo(sf::Vector2f pos, bool checkBorders, float speedMultiplier)
{
    bool result = true;

    sf::Vector2f movent(0,0);
    if(calcDistance(pos)>getSpeed()){
        //std::cout << "DIRIGIENDOSE a " << pos.x << ", " << pos.y << " estoy en " << getPosition().x  << ", " << getPosition().y << " y falta " << calcDistance(pos) << std::endl;
        //result = false;
        float catX =   pos.x - getPosition().x;
        float catY =  pos.y -getPosition().y ;
        movent.x = getSpeed()*(catX/(fabs(catX)+fabs(catY)))*speedMultiplier;
        movent.y = getSpeed()*(catY/(fabs(catX)+fabs(catY)))*speedMultiplier;
        result = move(movent, checkBorders);

    }

    return result;
}

sf::FloatRect Gladiator::getBorders() const
{
    return borders;
}

void Gladiator::setBorders(const sf::FloatRect &value)
{
    borders = value;
}

float Gladiator::getLife() const
{
    return life;
}

void Gladiator::setLife(float value)
{
    life = value;
}

double Gladiator::getFitness()
{
    return dna.getFitness();
}

int Gladiator::getKills() const
{
    return kills;
}

void Gladiator::setKills(int value)
{
    kills = value;
}

void Gladiator::update()
{
    //std::cout<< "size"<<labyrinthDirections.size() <<"\n";
    if(labyrinthDirections.size()>0){
        if(moveTo(labyrinthDirections.front())){
            labyrinthDirections.pop_front();
            //std::cout<< "size"<<labyrinthDirections.size() <<"\n";
        }
    }
    else if(runningAway && moveTo(shovePos, true, 2)){
        runningAway=false;
    }
    else if (hasClosest(dna.genes[AttackRadius]/10,1)){
        //std::cout << "attack1"<<std::endl;
        std::vector<Gladiator*> closest = getClosest(dna.genes[AttackRadius]/10,1);
        if(closest.size()>0){
            //std::cout << "attack2"<<std::endl;
            moveTo(closest[0]->getPosition(),   true);
            attack(closest[0]);

        }
    }
    else if( hasClosest(dna.genes[GladiatorDetectionRadius]*20,1) ){

        std::vector<Gladiator*> closest2 = getClosest(dna.genes[GladiatorDetectionRadius]*20,1);
        if(closest2.size()>0){
            moveTo(closest2[0]->getPosition(),   true);
        }
    }
    else {
    }
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

std::list<sf::Vector2f> Gladiator::getLabyrinthDirections() const
{
    return labyrinthDirections;
}

void Gladiator::setLabyrinthDirections(const std::list<sf::Vector2f> &value)
{
    labyrinthDirections = value;
}


/*void Gladiator::importLabyrinthDirections(const std::vector<sf::Vector2f> &value)
{
    labyrinthDirections.clear();
        for (int i = 0; i < value.size(); ++i) {
        labyrinthDirections.push_back(value[i]);
    }
}*/

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

bool Gladiator::hasClosest(float radius, int amount)
{
    float newDistance=0;
    bool result = false;
    for (int i = 0; i < gladiatorsList->size(); ++i) {
        newDistance =  calcDistance(gladiatorsList->operator [](i).getPosition());
        if(newDistance<radius ){
            result = true;
            break;
        }
    }
    return result;
}

std::vector<Gladiator* > Gladiator::getClosest(float radius, int amount)
{
    std::vector<Gladiator *> closest;
    float distance = 10000;
    float newDistance=0;
    for (int i = 0; i < gladiatorsList->size(); ++i) {
        newDistance=  calcDistance(gladiatorsList->operator [](i).getPosition());
        if(newDistance<radius && newDistance<distance ){
            if(closest.size()==0){
                closest.push_back(& gladiatorsList->operator [](i));
            }
            else{
                closest[0] = & gladiatorsList->operator [](i);
            }
        }
    }
    return closest;

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
    //    distance.x = sprite.getPosition().x - pos.x;
    //    distance.y = sprite.getPosition().y - pos.y;
    //float distance = 0;
    distance.x = getPosition().x - pos.x;
    distance.y = getPosition().y - pos.y;
    return  sqrt(pow(distance.x, 2) + pow(distance.y, 2));

}


void Gladiator::sortByDistance(std::vector<Gladiator*> *list){
    sortByDistance( list, 0, gladiatorsList->size()-1);
}

void Gladiator::importLabyrinthDirections(const std::vector<sf::Vector2f> &value)
{
    labyrinthDirections.clear();
    for (int i = value.size()-1; i >=0; i--) {
        labyrinthDirections.push_back(value[i]);
    }
}

void Gladiator::sortByDistance(std::vector<Gladiator*> *list, int left, int right)
{
    int i = left, j = right;
    Gladiator *tmp;
    //int pivot = list->operator []((left + right) / 2).getFitness();
    float pivot = calcDistance(list->operator[]((left + right) / 2)->getPosition());
            /* partition */
            while (i <= j) {
            //while (list->operator [](i).getFitness() < pivot)
            while ( calcDistance(list->operator [](i)->getPosition()) < pivot)
            i++;
    //while (list->operator [](j).getFitness() > pivot)
    while (calcDistance(list->operator [](j)->getPosition()) > pivot)
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
