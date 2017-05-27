//
// Created by jimena on 18/05/17.
//

#include "gladiatorManager.h"

gladiatorManager::gladiatorManager() {
    srand((unsigned) time(&t));

    bg1Tex.loadFromFile("Resources/Background.jpg");
    bg1Sprite.setTexture(bg1Tex);
    bg1Sprite.setPosition(0,0);

    intiZoneTexture.loadFromFile("Resources/cuadricula.jpg");
    coliseumTexture.loadFromFile("Resources/Coliseum.jpg");
    intiZoneSpriteL.setTexture(intiZoneTexture);
    intiZoneSpriteL.setPosition(0,175);
    intiZoneSpriteR.setTexture(intiZoneTexture);
    intiZoneSpriteR.setPosition(1150,175);
    coliseumSprite.setTexture(coliseumTexture);
    coliseumSprite.setPosition(450,0);

//    texture.loadFromFile("Resources/knight.png");

//    sprite.setTexture(texture);
//    sprite.setPosition(300,200);
//    sprite.setScale(-0.3,-0.3);

//    bg1Tex.loadFromFile("Resources/fondo.png");
//    bg1Tex.setSmooth(false);
//    bg1Tex.setRepeated(true);
//    bg1Sprite.setTexture(bg1Tex);
//    bg1Sprite.setScale(20,20);



    Gtexture1.setSmooth(true);
    Gtexture1.loadFromFile("Resources/bronze.png");
    Gtexture2.setSmooth(true);
    Gtexture2.loadFromFile("Resources/black.png");
    gladiator.sprite.setScale(-0.3,-0.3);

    cycleClock.restart();

    population.inicializePopulation(10);


    borders.height = 800;
    borders.width=700;
    borders.top=10;
    borders.left=450;


}

sf::FloatRect gladiatorManager::getBorders() const
{
    return borders;
}

void gladiatorManager::setBorders(const sf::FloatRect &value)
{
    borders = value;
}

int gladiatorManager::run(sf::RenderWindow &window) {
    std::list<sf::Vector2f> labyrinthDirections;

    for (int j = 0; j <10 ; ++j) {
        labyrinthDirections.clear();
        labyrinthDirections.push_back(  sf::Vector2f( 500+50*j  ,500+50*j   ) );
        labyrinthDirections.push_back(  sf::Vector2f( 700+50*j  ,500+50*j    ) );
        labyrinthDirections.push_back(  sf::Vector2f( 400+50*j  ,300+50*j    ) );
        labyrinthDirections.push_back(  sf::Vector2f( 600+50*j  ,500+50*j    ) );
        labyrinthDirections.push_back(  sf::Vector2f( 300+50*j  ,100+50*j    ) );

        gladiator.setDna(population.getPopulation()[j]);
        gladiator.setTexture(&Gtexture1);
        gladiator.sprite.setScale(0.1,0.1);
        gladiator.setPosition(sf::Vector2f(300,300));
        gladiator.setLabyrinthDirections(labyrinthDirections);
        gladiator.setGladiatorsList(&gladiatorList2);
        gladiator.setBorders(borders);
        gladiatorList1.push_back(gladiator);
    }

    for (int j = 0; j <10 ; ++j) {
        labyrinthDirections.clear();
        labyrinthDirections.push_back(  sf::Vector2f( 700+50*j  ,500+50*j   ) );
        labyrinthDirections.push_back(  sf::Vector2f( 900+50*j  ,500+50*j    ) );
        labyrinthDirections.push_back(  sf::Vector2f( 600+50*j  ,300+50*j    ) );
        labyrinthDirections.push_back(  sf::Vector2f( 800+50*j  ,500+50*j    ) );
        labyrinthDirections.push_back(  sf::Vector2f( 400+50*j  ,100+50*j    ) );

        gladiator.setDna(population.getPopulation()[j]);
        gladiator.setTexture(&Gtexture2);
        gladiator.sprite.setScale(0.1,0.1);
        gladiator.setPosition(sf::Vector2f(300,300));
        gladiator.setLabyrinthDirections(labyrinthDirections);
        gladiator.setGladiatorsList(&gladiatorList1);
        gladiator.setBorders(borders);

        gladiatorList2.push_back(gladiator);
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
        window.clear(sf::Color::Black);
        window.draw(bg1Sprite);
        window.draw(coliseumSprite);
        window.draw(intiZoneSpriteR);
        window.draw(intiZoneSpriteL);

//        sf::Texture texture;
//        if (!texture.loadFromFile("Resources/fondo.png"))
//        {
//            // error...
//        }
//        sf::Sprite sprite;
//        sprite.setTexture(texture);
//
//        window.draw(sprite);



            //gladiatorList.clear();

                //window.draw(bg1Sprite);
                for (int i = 0; i < gladiatorList1.size(); ++i) {
                    if(gladiatorList1[i].isAlive()){
                    gladiatorList1[i].update();
                    gladiatorList1[i].draw(window);
                    }
                    else{
                        gladiatorList1[i].setPosition(sf::Vector2f(100000,100000));
                    }
                }
                for (int i = 0; i < gladiatorList2.size(); ++i) {
                    if(gladiatorList2[i].isAlive()){
                    gladiatorList2[i].update();
                    gladiatorList2[i].draw(window);
                }
                    else{
                        gladiatorList2[i].setPosition(sf::Vector2f(100000,100000));
                    }
                }
                window.display();

    }


    return 0;
}
