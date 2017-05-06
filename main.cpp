#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "dna.h"
#include"populationmanager.h"

//using namespace std;
const int W = 1200;
const int H = 800;
int main(int argc, char *argv[])
{
    std::cout << "Hello World!" << std::endl;
    sf::RenderWindow app(sf::VideoMode(W, H), "Genetic Colosseum");
    app.setFramerateLimit(60);
    sf::Texture texture;
    texture.loadFromFile("images/attack_1.png");
    sf::Sprite sprite(texture);
    sprite.setPosition(300,200);
    sprite.setScale(0.3,0.3);
    PopulationManager population;
    population.inicializePopulation(3000);
    population.calcFitnessForEach();

    for (int i = 0; i < 100; ++i) {
        population.setProbabilityForEach();
        population.createNextGeneration();
        population.calcFitnessForEach();
        population.sortByFitness();
        std::cout << population.getPopulation().operator [](population.getPopulation().size()-1).getFitness() << std::endl;
        }



    while (!app.isOpen()){
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();
        }
        //sprite.draw(app);
        sprite.move(2,0);
        app.draw(sprite);
        app.display();
    }


    return 0;
}
