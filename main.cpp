#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "dna.h"
#include"populationmanager.h"
#include"gladiator.h"

//using namespace std;
const int W = 1200;
const int H = 800;
int main(int argc, char *argv[])
{
    time_t t;
    srand((unsigned) time(&t));
    sf::RenderWindow app(sf::VideoMode(W, H), "Genetic Colosseum");
    app.setFramerateLimit(60);
    sf::Texture texture;
    texture.loadFromFile("images/attack_1.png");
    sf::Sprite sprite(texture);
    sprite.setPosition(300,200);
    sprite.setScale(0.3,0.3);
    PopulationManager population;
    population.inicializePopulation(300);
    population.calcFitnessForEach();
    std::cout<<HorizontalCost<<"HorizontalCost"<<std::endl;

    for (int i = 0; i < 100; ++i) {
        population.setProbabilityForEach();
        population.createNextGeneration();
        population.calcFitnessForEach();
        population.sortByFitness();
        DNA best=population.getPopulation().operator [](population.getPopulation().size()-1);
        /*
        std::cout << population.getPopulation().operator [](population.getPopulation().size()-1).getFitness() << std::endl;
        std::cout<<"genes";
        for (int j = 0; j < 11; ++j) {
            std::cout<<best.genes[j]<<"   ";
        }
        std::cout<<"___\n";

        */
        }
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
Gtexture.loadFromFile("images/attack_1.png");
gladiator.sprite.setScale(0.3,0.3);

gladiator.setTexture(&Gtexture);
for (int i = 0; i < 4; ++i) {
    gladiator.setDna(DNAManager::createRandomDNA());
    gladiator.sprite.setScale(0.3,0.3);
    gladiator.setTexture(&Gtexture);
    gladiator.setPosition(sf::Vector2f(600,200*i));
    gladiatorList.push_back(gladiator);
}

    while (app.isOpen()){
        app.draw(bg1Sprite);

        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();
        }
        //sprite.draw(app);
        //sprite.move(2,0);
        //app.draw(sprite);
        for (int i = 0; i < gladiatorList.size(); ++i) {
            gladiatorList[i].update();
            gladiatorList[i].draw(app);
        }
        //gladiator.sprite.move(2,0);

        app.display();

    }


    return 0;
}
