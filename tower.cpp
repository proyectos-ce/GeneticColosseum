#include "tower.h"

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
}
