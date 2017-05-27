//
// Created by jimena on 18/05/17.
//

#include <zconf.h>
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

void gladiatorManager::setObstacles(Grid* grid, sf::RenderWindow &window){
    grid->solve(&gladiator);
    for(int i =0; i<grid->obstacleCells.size(); i++){
            sf::Sprite obstacleSprite;
            obstacleSprite.setTexture(texturesArray[0 + (rand() % (2 + 1))]);
            if(grid->gridSide.compare("R") == 0)
                obstacleSprite.setPosition(grid->obstacleCells[i]->col*45+1150, grid->obstacleCells[i]->row*45+175);
            else{
                obstacleSprite.setPosition(grid->obstacleCells[i]->col*45, grid->obstacleCells[i]->row*45+175);
            }
            spritesArray.push_back(obstacleSprite);
        }


//    grid->generatePixelPath();


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
//            labyrinthDirections.push_back(  sf::Vector2f( 500+50*j  ,100+50*j    ) );

            gladiator.setDna(population.getPopulation()[j]);
            gladiator.setTexture(&Gtexture1);
            gladiator.sprite.setScale(0.1,0.1);
            gladiator.setPosition(sf::Vector2f(1555,220));
//            gladiator.setLabyrinthDirections(labyrinthDirections);
            rightGrid->solve(&gladiator);
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
//            labyrinthDirections.push_back(  sf::Vector2f( 600+50*j  ,100+50*j    ) );

            gladiator.setDna(population.getPopulation()[j]);
            gladiator.setTexture(&Gtexture2);
            gladiator.sprite.setScale(0.1,0.1);
            gladiator.setPosition(sf::Vector2f(0,220));
            leftGrid->solve(&gladiator);
//            gladiator.setLabyrinthDirections(labyrinthDirections);
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
        drawObstacles(window);
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


