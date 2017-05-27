#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "dna.h"
#include"populationmanager.h"
#include"gladiator.h"
#include "screens.h"
#include "gladiatorManager.h"

//#include "Grid.h"


const int W = 1600;
const int H = 800;
int main(int argc, char *argv[])
{

    
    std::vector<screen*> screens;
    int screen = 0;
    std::string ip = "";

    sf::RenderWindow app(sf::VideoMode(W, H), "Genetic Colosseum");
    app.setFramerateLimit(60);

    menu menuScreen;
    screens.push_back(&menuScreen);


    gladiatorManager gameManager;
    screens.push_back(&gameManager);


    while(screen >=0){
        screen = screens[screen]->run(app, ip);
    }

    return EXIT_SUCCESS;
}

