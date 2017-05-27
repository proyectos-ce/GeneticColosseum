#ifndef TOWER_H
#define TOWER_H

#include <SFML/Graphics.hpp>

class Tower
{
public:
    Tower();
    sf::Sprite sprite;
    sf::Texture texture;
    void set_place(int x, int y);
    void update(sf::RenderWindow &window);
private:

};

#endif // TOWER_H
