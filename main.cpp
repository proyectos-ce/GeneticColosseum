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


//using namespace std;
const int W = 1200;
const int H = 800;
int main(int argc, char *argv[])
{

    
    std::vector<screen*> screens;
    int screen = 0;

    sf::RenderWindow app(sf::VideoMode(W, H), "Genetic Colosseum");
    app.setFramerateLimit(60);

    menu menuScreen;
    screens.push_back(&menuScreen);


    gladiatorManager gameManager;
    screens.push_back(&gameManager);


    while(screen >=0){
        screen = screens[screen]->run(app);


    std::list<sf::Vector2f> labyrinthDirections;
    labyrinthDirections.push_back(  sf::Vector2f( 200  ,100   ) );
    labyrinthDirections.push_back(  sf::Vector2f( 400  ,100   ) );
    labyrinthDirections.push_back(  sf::Vector2f( 400  ,300   ) );
    labyrinthDirections.push_back(  sf::Vector2f( 600  ,500   ) );
    labyrinthDirections.push_back(  sf::Vector2f( 800  ,100   ) );
    //labyrinthDirections.push_back(  sf::Vector2f( 450  ,300   ) );
    //labyrinthDirections.push_back(  sf::Vector2f( 800  ,600   ) );
    //labyrinthDirections.push_back(  sf::Vector2f( 100  ,100   ) );

    }

    return EXIT_SUCCESS;
}
