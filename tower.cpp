#include "tower.h"
#include "gladiator.h"

Tower::Tower()
{
    texture.loadFromFile("Resources/cannon_tower.png");
    sprite.setTexture(texture);
    sprite.scale(sf::Vector2f(0.16,0.16 ));
}
void Tower::update(sf::RenderWindow &window) {
    window.draw(sprite);
}
void Tower::set_place(int x, int y) {
    sprite.setPosition(x,y);
    pos_x=x;
    pos_y=y;
}


std::vector<Gladiator* > Tower::getClosest(float radius,std::vector<Gladiator> *gladiatorsList)
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

sf::Vector2f Tower::getPosition() {
    sf::Vector2f pos = sprite.getPosition();
    pos.x += sprite.getGlobalBounds().width/2;
    pos.y += sprite.getGlobalBounds().height;
    return pos;
}

float Tower::calcDistance(sf::Vector2f pos){
    sf::Vector2f distance;
    distance.x = getPosition().x - pos.x;
    distance.y = getPosition().y - pos.y;
    return  sqrt(pow(distance.x, 2) + pow(distance.y, 2));

}


void Tower::attack(Gladiator *gladiator) {

   // if (attackClock.getElapsedTime().asSeconds()>0.5){

    //    attackClock.restart();
    //}
    std::cout<< "putos" << std::endl ;
}