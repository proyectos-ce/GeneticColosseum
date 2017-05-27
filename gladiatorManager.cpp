//
// Created by jimena on 18/05/17.
//

#include "gladiatorManager.h"
#include "stats.h"

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

    Http::server = "http://geneticserver.herokuapp.com";
    dnaList1 = Http::getFirst(1);
    dnaList2 = Http::getFirst(2);

}

void gladiatorManager::extractDNA()
{
    dnaList1.clear();

    for (int i = 0; i < gladiatorList1.size(); ++i) {
        dnaList1.push_back(gladiatorList1[i].dna);
    }


    for (int i = 0; i < deadGladiatorList1.size(); ++i) {
        dnaList1.push_back(deadGladiatorList1[i].dna);
    }
    deadGladiatorList1.clear();


    dnaList2.clear();

    for (int i = 0; i < gladiatorList2.size(); ++i) {
        dnaList2.push_back(gladiatorList2[i].dna);
    }


    for (int i = 0; i < deadGladiatorList2.size(); ++i) {
        dnaList2.push_back(deadGladiatorList2[i].dna);
    }
    deadGladiatorList2.clear();
    if (dnaList2.size()==0){
     int a =1;
    }
}

sf::FloatRect gladiatorManager::getBorders() const
{
    return borders;
}

void gladiatorManager::setBorders(const sf::FloatRect &value)
{
    borders = value;
}

int gladiatorManager::run(sf::RenderWindow &window, std::string& ip) {
    std::cout <<ip<<std::endl;
    std::list<sf::Vector2f> labyrinthDirections;


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

        gladiatorList1.clear();
        gladiatorList2.clear();
        //dnaList1 = Http::getNext(1, dnaList1);
        //dnaList2 = Http::getNext(2, dnaList2);

        for (int j = 0; j <dnaList1.size() ; ++j) {
            labyrinthDirections.clear();
            //for (int var = 0; var < 4; ++var) {
            //    labyrinthDirections.push_back(  sf::Vector2f( 100  ,100    ) );
             //   labyrinthDirections.push_back(  sf::Vector2f( 100  ,400    ) );
           // }

            labyrinthDirections.push_back(  sf::Vector2f( 500  ,100    ) );
            gladiator.setDna(dnaList1[j]);
            gladiator.setTexture(&Gtexture1);
            gladiator.sprite.setScale(0.1,0.1);
            gladiator.setPosition(sf::Vector2f(300,300));
            gladiator.setLabyrinthDirections(labyrinthDirections);
            gladiator.setGladiatorsList(&gladiatorList2);
            gladiator.setBorders(borders);
            gladiatorList1.push_back(gladiator);
        }

        for (int j = 0; j <dnaList2.size() ; ++j) {
            labyrinthDirections.clear();
            //for (int var = 0; var < 4; ++var) {
            //    labyrinthDirections.push_back(  sf::Vector2f( 1200  ,100    ) );
            //    labyrinthDirections.push_back(  sf::Vector2f( 1200  ,400    ) );
            //}
            labyrinthDirections.push_back(  sf::Vector2f( 800  ,100) );
            gladiator.setDna(dnaList2[j]);
            gladiator.setTexture(&Gtexture2);
            gladiator.sprite.setScale(0.1,0.1);
            gladiator.setPosition(sf::Vector2f(900,300));
            gladiator.setLabyrinthDirections(labyrinthDirections);
            gladiator.setGladiatorsList(&gladiatorList1);
            gladiator.setBorders(borders);
            gladiatorList2.push_back(gladiator);
        }




        roundClock.restart();
        while(roundClock.getElapsedTime().asSeconds()<ROUND_TIME){
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
            //_____________________________________________________________DIBUJAR LOS TEXTOS
            //Stats.update_gladiator_stats(window, );
            Stats.update_gen_stats(window,generation, ROUND_TIME-roundClock.getElapsedTime().asSeconds());
            Stats.update_gladiator_stats(window, &gladiatorList2[2]);
            window.display();

        }
        //roundClock.restart();
        generation++;
        extractDNA();
        dnaList1 = Http::getNext(1, dnaList1);
        dnaList2 = Http::getNext(2, dnaList2);
    }


    return 0;
}
