#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>
#include <vector>



class Entity
{
public:
    Entity();
    sf::Texture *texture;
    sf::Sprite sprite;
    virtual void draw(sf::RenderWindow &window);
    virtual void update(float time);
    sf::Vector2f getPosition();
    void setPosition(const sf::Vector2f &value);
    sf::Texture *getTexture() const;
    void setTexture(sf::Texture *value);

private:
    sf::Vector2f position;


};

#endif // ENTITY_H
