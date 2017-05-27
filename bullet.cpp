//
// Created by danielc on 27/05/17.
//

#include "bullet.h"

bullet::bullet() {
    texture.loadFromFile("Resources/fireball.png");
    sprite.setTexture(texture);
    sprite.scale(sf::Vector2f(0.16,0.16 ));
}

void bullet::update(sf::RenderWindow &window) {
    window.draw(sprite);
}