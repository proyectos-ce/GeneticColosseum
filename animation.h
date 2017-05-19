#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML/Graphics.hpp>


class Animation
{
public:
    Animation();
    sf::Texture *texture;
    sf::Sprite sprite;
    void update(float time);
    void draw(sf::RenderWindow &window);
    sf::Vector2i spriteMatrix;
    void setPosition(sf::Vector2f position);
};

class AnimationRoutine
{
public:
    AnimationRoutine();
};

enum Animations {
    Walk,
    Attack,
    Defent,
    Jump,
    Dead
};

#endif // ANIMATION_H
