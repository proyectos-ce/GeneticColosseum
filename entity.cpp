#include "entity.h"

Entity::Entity()
{

}

sf::Texture *Entity::getTexture() const
{
    return texture;
}

void Entity::setTexture(sf::Texture *value)
{
    texture = value;
    sprite.setTexture(*texture);

}

void Entity::draw(sf::RenderWindow &window)
{
    //animation.draw(sf::RenderWindow &window);
    window.draw(sprite);
}


void Entity::update(float time)
{
    /*sf::Vector2f pos = position;
    pos.x -= sprite.getLocalBounds().width/2;
   pos.y -= sprite.getLocalBounds().height;
    sprite.setPosition(pos);
    */
}

sf::Vector2f Entity::getPosition()
{
    //sf::Vector2f pos = sprite.getPosition();
    //pos.x += sprite.getLocalBounds().width/2;
   // pos.y += sprite.getLocalBounds().width/2;
    return position;
}

void Entity::setPosition(const sf::Vector2f &value)
{

    position = value;
    sf::Vector2f pos = position;
    //pos.x -= sprite.getLocalBounds().width/2;
    //pos.y -= sprite.getLocalBounds().height;
    pos.x -= texture->getSize().x/2;
    pos.x -= texture->getSize().y/2;
    sprite.setPosition(pos);

}
