//
// Created by jimena on 18/05/17.
//

#include <zconf.h>
#include "gladiatorManager.h"
#include "stats.h"
#include "tower.h"

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


    for (int i=0; i<5;i++){
        towerlist_izq.push_back(torre);
    }
    for (int i=0; i<5;i++){
        towerlist_der.push_back(torre);
    }

///obstaculos
    crystalTexture.loadFromFile("Resources/crystal.png");
    trunkTexture.loadFromFile("Resources/trunk.png");
    holeTexture.loadFromFile("Resources/hole.png");

    texturesArray.push_back(crystalTexture);
    texturesArray.push_back(holeTexture);
    texturesArray.push_back(trunkTexture);


    Gtexture1.setSmooth(true);
    Gtexture1.loadFromFile("Resources/bronze.png");
    Gtexture2.setSmooth(true);
    Gtexture2.loadFromFile("Resources/black.png");

    cycleClock.restart();

    population.inicializePopulation(10);

    borders.height = 800;
    borders.width=700;
    borders.top=10;
    borders.left=450;



}

void gladiatorManager::extractDNA()
{
    dnaList1.clear();
    for (int i = 0; i < gladiatorList1.size(); ++i) {
         dnaList1.push_back(gladiatorList1[i].dna);
    }
    gladiatorList1.clear();

    for (int i = 0; i < deadGladiatorList1.size(); ++i) {
        dnaList1.push_back(deadGladiatorList1[i].dna);
    }
    deadGladiatorList1.clear();

    dnaList2.clear();
    for (int i = 0; i < gladiatorList2.size(); ++i) {
         dnaList2.push_back(gladiatorList2[i].dna);
    }
    gladiatorList2.clear();

    for (int i = 0; i < deadGladiatorList2.size(); ++i) {
        dnaList1.push_back(deadGladiatorList1[i].dna);
    }
    deadGladiatorList1.clear();

}

sf::FloatRect gladiatorManager::getBorders() const
{
    return borders;
}

void gladiatorManager::setBorders(const sf::FloatRect &value)
{
    borders = value;
}

void gladiatorManager::setObstacles(Grid* grid, sf::RenderWindow &window){
    for(int i =0; i<grid->obstacleCells.size(); i++){
            sf::Sprite obstacleSprite;
            obstacleSprite.setTexture(texturesArray[0 + (rand() % (2 + 1))]);
            if(grid->gridSide.compare("R") == 0)
                obstacleSprite.setPosition(grid->obstacleCells[i]->col*45, grid->obstacleCells[i]->row*45+175);
            else{
                obstacleSprite.setPosition(grid->obstacleCells[i]->col*45+1150, grid->obstacleCells[i]->row*45+175);
            }
            spritesArray.push_back(obstacleSprite);
        }
    }


void gladiatorManager::drawObstacles(sf::RenderWindow &window) {
    for(int i=0; i<spritesArray.size(); i++){
        window.draw(spritesArray[i]);
    }
}

int gladiatorManager::run(sf::RenderWindow &window, std::string& ip) {

    rightGrid = new Grid('R');
    leftGrid = new Grid('L');

    setObstacles(rightGrid, window);
    setObstacles(leftGrid, window);

    std::cout <<ip<<std::endl;
    std::list<sf::Vector2f> labyrinthDirections;

    for (int var = 0; var < 3; ++var) {


        for (int j = 0; j <10 ; ++j) {
            labyrinthDirections.clear();
            /*labyrinthDirections.push_back(  sf::Vector2f( 500+50*j  ,500+50*j   ) );
        labyrinthDirections.push_back(  sf::Vector2f( 700+50*j  ,500+50*j    ) );
        labyrinthDirections.push_back(  sf::Vector2f( 400+50*j  ,300+50*j    ) );
        labyrinthDirections.push_back(  sf::Vector2f( 600+50*j  ,500+50*j    ) );*/
            labyrinthDirections.push_back(  sf::Vector2f( 500+50*j  ,100+50*j    ) );

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
            /*labyrinthDirections.clear();
        labyrinthDirections.push_back(  sf::Vector2f( 700+50*j  ,500+50*j   ) );
        labyrinthDirections.push_back(  sf::Vector2f( 900+50*j  ,500+50*j    ) );
        labyrinthDirections.push_back(  sf::Vector2f( 600+50*j  ,300+50*j    ) );
        labyrinthDirections.push_back(  sf::Vector2f( 800+50*j  ,500+50*j    ) );*/
            labyrinthDirections.push_back(  sf::Vector2f( 600+50*j  ,100+50*j    ) );

            gladiator.setDna(population.getPopulation()[j]);
            gladiator.setTexture(&Gtexture2);
            gladiator.sprite.setScale(0.1,0.1);
            gladiator.setPosition(sf::Vector2f(300,300));
            gladiator.setLabyrinthDirections(labyrinthDirections);
            gladiator.setGladiatorsList(&gladiatorList1);
            gladiator.setBorders(borders);

            gladiatorList2.push_back(gladiator);
        }
    }

    sf::Sprite crystalSprite(crystalTexture);
    crystalSprite.setPosition(90, 175);

    sf::Sprite trunkSprite(trunkTexture);
    trunkSprite.setPosition(135,220);

    sf::Sprite holeSprite(holeTexture);
    holeSprite.setPosition(180, 265);

    while (window.isOpen()){


        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                exit(0);
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                return 0;
        }
        window.clear(sf::Color::Black);

        window.draw(bg1Sprite);
        window.draw(coliseumSprite);
        window.draw(intiZoneSpriteR);
        window.draw(intiZoneSpriteL);

//        window.draw(crystalSprite);
//        window.draw(trunkSprite);
//        window.draw(holeSprite);

//        sf::Texture texture;
//        if (!texture.loadFromFile("Resources/fondo.png"))
//        {
//            // error...
//        }
//        sf::Sprite sprite;
//        sprite.setTexture(texture);
//
//        window.draw(sprite);

        gladiatorList1.clear();
        gladiatorList2.clear();
        for (int var = 0; var < 30; ++var) {
            for (int j = 0; j <10 ; ++j) {
                labyrinthDirections.clear();
                /*labyrinthDirections.push_back(  sf::Vector2f( 500+50*j  ,500+50*j   ) );
            labyrinthDirections.push_back(  sf::Vector2f( 700+50*j  ,500+50*j    ) );
            labyrinthDirections.push_back(  sf::Vector2f( 400+50*j  ,300+50*j    ) );
            labyrinthDirections.push_back(  sf::Vector2f( 600+50*j  ,500+50*j    ) );*/
                labyrinthDirections.push_back(  sf::Vector2f( 500+50*j  ,100+50*j    ) );

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
                /*labyrinthDirections.push_back(  sf::Vector2f( 700+50*j  ,500+50*j   ) );
            labyrinthDirections.push_back(  sf::Vector2f( 900+50*j  ,500+50*j    ) );
            labyrinthDirections.push_back(  sf::Vector2f( 600+50*j  ,300+50*j    ) );
            labyrinthDirections.push_back(  sf::Vector2f( 800+50*j  ,500+50*j    ) );*/
                labyrinthDirections.push_back(  sf::Vector2f( 600+50*j  ,100+50*j    ) );

                gladiator.setDna(population.getPopulation()[j]);
                gladiator.setTexture(&Gtexture2);
                gladiator.sprite.setScale(0.1,0.1);
                gladiator.setPosition(sf::Vector2f(300,300));
                gladiator.setLabyrinthDirections(labyrinthDirections);
                gladiator.setGladiatorsList(&gladiatorList1);
                gladiator.setBorders(borders);

                gladiatorList2.push_back(gladiator);
            }

        }



        while(roundClock.getElapsedTime().asSeconds()<30){
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    exit(0);
                if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                    return 0;
            }
            window.clear(sf::Color::Black);
            window.draw(bg1Sprite);
            window.draw(coliseumSprite);
            window.draw(intiZoneSpriteR);
            window.draw(intiZoneSpriteL);


            drawObstacles(window);

            for (int i =  gladiatorList1.size()-1; i >=0; --
                 i) {
                if(gladiatorList1[i].isAlive()){
                    gladiatorList1[i].update();
                    gladiatorList1[i].draw(window);
                }
                else{
                    deadGladiatorList1.push_back(gladiatorList1[i]);
                    gladiatorList1.erase(gladiatorList1.begin()+i);
                }
            }
            for (int i =  gladiatorList2.size()-1; i >=0; --i) {
                if(gladiatorList2[i].isAlive()){
                    gladiatorList2[i].update();
                    gladiatorList2[i].draw(window);
                }
                else{
                    deadGladiatorList2.push_back(gladiatorList2[i]);
                    gladiatorList2.erase(gladiatorList2.begin()+i);
                }
            }

            for(int i = towerlist_izq.size()-1; i>=0; --i){
                int x = -6 + (i*45);
                int y = 138 + (i*45);
                towerlist_izq[i].set_place(x,y);
            }
            for(int i = towerlist_izq.size()-1; i>=0; --i){
                towerlist_izq[i].update(window);
            }

            for(int i = towerlist_der.size()-1; i>=0; --i){
                int x = 1144 + (i*45);
                int y = 138 + (i*45);
                towerlist_der[i].set_place(x,y);
            }

            for(int i = towerlist_der.size()-1; i>=0; --i){
                towerlist_der[i].update(window);
            }
           // torre2.update(window);
            //_____________________________________________________________DIBUJAR LOS TEXTOS
            //Stats.update_gladiator_stats(window, );
            Stats.update_gen_stats(window,1,1);
            //torre.update(window);



            window.display();

        }
        roundClock.restart();
        extractDNA();
    }


    return 0;
}


