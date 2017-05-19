//
// Created by jimena on 18/05/17.
//

#include "gladiatorManager.h"

gladiatorManager::gladiatorManager() {
    srand((unsigned) time(&t));

    texture.loadFromFile("Resources/knight.png");

    sprite.setTexture(texture);
    sprite.setPosition(300,200);
    sprite.setScale(-0.3,-0.3);

    bg1Tex.loadFromFile("Resources/background.png");
    bg1Tex.setSmooth(false);
    bg1Tex.setRepeated(true);
    bg1Sprite.setTexture(bg1Tex);
    bg1Sprite.setScale(20,20);

    Gtexture.setSmooth(true);
    Gtexture.loadFromFile("Resources/knight.png");
    gladiator.sprite.setScale(-0.3,-0.3);

    cycleClock.restart();

    population.inicializePopulation(10);



    labyrinthDirections.push_back(  sf::Vector2f( 200  ,100   ) );
    labyrinthDirections.push_back(  sf::Vector2f( 400  ,100   ) );
    labyrinthDirections.push_back(  sf::Vector2f( 400  ,300   ) );
    labyrinthDirections.push_back(  sf::Vector2f( 600  ,500   ) );
    labyrinthDirections.push_back(  sf::Vector2f( 800  ,100   ) );


}

int gladiatorManager::run(sf::RenderWindow &window) {
    while (window.isOpen()){

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                return 0;
        }

    }


    return 0;
}
