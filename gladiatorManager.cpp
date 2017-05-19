//
// Created by jimena on 18/05/17.
//

#include "gladiatorManager.h"

gladiatorManager::gladiatorManager() {
    srand((unsigned) time(&t));

    texture.loadFromFile("Resources/knight.png");

    sprite.setTexture(texture);
    sprite.setPosition(300,200);
    sprite.setScale(0.3,0.3);

    bg1Tex.loadFromFile("Resources/background.png");
    bg1Tex.setSmooth(false);
    bg1Tex.setRepeated(true);
    bg1Sprite.setTexture(bg1Tex);
    bg1Sprite.setScale(20,20);

    Gtexture.setSmooth(true);
    Gtexture.loadFromFile("Resources/knight.png");
    gladiator.sprite.setScale(0.3,0.3);

    cycleClock.restart();

    population.inicializePopulation(500);

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

        for (int gen = 0; gen < 200; ++gen) {
            resultPop.clear();
            gladiatorList.clear();

            for (int i = 0; i < population.population.size(); ++i) {
                gladiator.setDna(population.getPopulation()[i]);
                gladiator.setTexture(&Gtexture);
                gladiator.sprite.setScale(0.3,0.3);
                gladiator.setPosition(sf::Vector2f(150,150));

                gladiatorList.push_back(gladiator);
            }


            while (cycleClock.getElapsedTime().asMilliseconds() < 4000/Xspeed) {
                window.draw(bg1Sprite);
                for (int i = 0; i < gladiatorList.size(); ++i) {
                    gladiatorList[i].update();
                    gladiatorList[i].draw(window);
                }
                window.display();


                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        exit(0);
                    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                        return 0;
                }

            }
            cycleClock.restart();
            for (int i = 0; i < gladiatorList.size(); ++i) {
                gladiatorList[i].testCalcFitness(sf::Vector2f(1000, 600));
                resultPop.push_back(gladiatorList[i].dna);
            }
            population.setPopulation(resultPop);
            population.sortByFitness();
            std::cout<<"gen  "<<gen <<"best "<<population.population[0].getFitness()<<"\n";
            population.createNextGeneration();
        }
        break;

    }


    return 0;
}
