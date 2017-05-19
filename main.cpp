#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "dna.h"
#include"populationmanager.h"
#include"gladiator.h"
#include "Grid.h"

//using namespace std;
const int W = 1200;
const int H = 800;
int main(int argc, char *argv[])
{
    Grid grid;
    grid.printGrid();
    grid.solve();
    grid.printPath();
    time_t t;
    srand((unsigned) time(&t));
    sf::RenderWindow app(sf::VideoMode(W, H), "Genetic Colosseum");
    app.setFramerateLimit(60);
    sf::Texture texture;
    texture.loadFromFile("Resources/knight.png");
    sf::Sprite sprite(texture);
    sprite.setPosition(300,200);
    sprite.setScale(0.3,0.3);

    sf::Texture bg1Tex;
    sf::Sprite bg1Sprite;
    bg1Tex.loadFromFile("Resources/background.png");
    bg1Tex.setSmooth(false);
    bg1Tex.setRepeated(true);
    bg1Sprite.setTexture(bg1Tex);
    bg1Sprite.setScale(20,20);








    std::vector<Gladiator> gladiatorList;
    Gladiator gladiator;
    sf::Texture Gtexture;
    Gtexture.setSmooth(true);
    Gtexture.loadFromFile("Resources/knight.png");
    gladiator.sprite.setScale(0.3,0.3);

    sf::Clock cycleClock;
    cycleClock.restart();
    std::vector<DNA> resultPop;

    PopulationManager population;
    population.inicializePopulation(500);

    sf::CircleShape target(10);
    target.setFillColor(sf::Color(150, 50, 250));
    target.setPosition(1000,600);



    while (app.isOpen()){

        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();
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
                app.draw(bg1Sprite);
                for (int i = 0; i < gladiatorList.size(); ++i) {
                    gladiatorList[i].update();
                    gladiatorList[i].draw(app);
                    app.draw(target);
                }
                app.display();


                while (app.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        app.close();
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