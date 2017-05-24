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

//    bg1Tex.loadFromFile("Resources/fondo.png");
//    bg1Tex.setSmooth(false);
//    bg1Tex.setRepeated(true);
//    bg1Sprite.setTexture(bg1Tex);
//    bg1Sprite.setScale(20,20);



    Gtexture.setSmooth(true);
    Gtexture.loadFromFile("Resources/knight.png");
    gladiator.sprite.setScale(-0.3,-0.3);

    cycleClock.restart();

    population.inicializePopulation(10);




}

int gladiatorManager::run(sf::RenderWindow &window) {
    std::list<sf::Vector2f> labyrinthDirections;
    labyrinthDirections.push_back(  sf::Vector2f( 500  ,500  ) );
    labyrinthDirections.push_back(  sf::Vector2f( 700  ,500   ) );
    labyrinthDirections.push_back(  sf::Vector2f( 400  ,300   ) );
    labyrinthDirections.push_back(  sf::Vector2f( 600  ,500   ) );
    labyrinthDirections.push_back(  sf::Vector2f( 100  ,100   ) );

    for (int j = 0; j < 3; ++j) {
        gladiator.setDna(population.getPopulation()[1]);
        gladiator.setTexture(&Gtexture);
        gladiator.sprite.setScale(0.1,0.1);
        gladiator.setPosition(sf::Vector2f(300,300));
        gladiator.setLabyrinthDirections(labyrinthDirections);
        gladiatorList.push_back(gladiator);
    }




    while (window.isOpen()){

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                return 0;
        }

        sf::Texture texture;
        if (!texture.loadFromFile("Resources/fondo.png"))
        {
            // error...
        }
        sf::Sprite sprite;
        sprite.setTexture(texture);

        window.draw(sprite);



            //gladiatorList.clear();

                //window.draw(bg1Sprite);
                for (int i = 0; i < gladiatorList.size(); ++i) {
                    gladiatorList[i].update();
                    gladiatorList[i].draw(window);
                }



                window.display();

    }


    return 0;
}
