//
// Created by jimena on 18/05/17.
//
#include <iostream>
#include "menu.h"

menu::menu() {}

int menu::run(sf::RenderWindow &window, std::string &ip) {
    sf::Event event;

    sf::Texture backgroundTexture;
    sf::Texture coliseumTexture;
    sf::Sprite coliseumSprite;
    sf::Sprite backgroundSprite;
    sf::Font font;

    sf::Text titleLabel;
    sf::Text ipLabel;
    sf::Text ipStatus;
    sf::Text startLabel;

    bool running = true;
    int menuNumber = 0;
    std::string ipDirection;

    backgroundTexture.loadFromFile("Resources/Background.jpg");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(0,0);
    backgroundSprite.setTextureRect(sf::IntRect(0,0,1600,800));

    coliseumTexture.loadFromFile("Resources/coliseum.png");
    coliseumSprite.setTexture(coliseumTexture);
    coliseumSprite.setPosition(550,200);




    font.loadFromFile("Resources/CardsFont.TTF");

    titleLabel.setFont(font);
    titleLabel.setCharacterSize(80);
    titleLabel.setString("Genetic Colosseum");
    titleLabel.setPosition(20,20);
    titleLabel.setColor(sf::Color(73,183,108));
    titleLabel.setStyle(sf::Text::Italic);

    ipLabel.setFont(font);
    ipLabel.setCharacterSize(40);
    ipLabel.setString("IP Direction");
    ipLabel.setPosition(20, 180);

    ipStatus.setFont(font);
    ipStatus.setCharacterSize(40);
    ipStatus.setPosition(360, 180);
    ipStatus.setColor(sf::Color(73,183,108));


    startLabel.setFont(font);
    startLabel.setCharacterSize(40);
    startLabel.setString("Start");
    startLabel.setPosition(20, 250);


    while(running){
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                exit(0);
            }

            if(event.type == sf::Event::TextEntered && menuNumber ==0){
                ipDirection.push_back((char)event.text.unicode);
            }

            if(event.type == sf::Event::KeyPressed){
                switch (event.key.code){
                    case sf::Keyboard::Escape:
                        exit(0);
                    case sf::Keyboard::Up:
                        menuNumber--;
                        if(menuNumber<0)
                            menuNumber=0;
                        break;
                    case sf::Keyboard::Down:
                        menuNumber++;
                        if(menuNumber>1)
                            menuNumber=1;
                        break;
                    case sf::Keyboard::Return:
                        if(menuNumber==1)
                            ip = ipDirection;
                            return 1;
                    default:
                        break;
                }
            }

            if(event.key.code == sf::Keyboard::BackSpace && ipDirection.size()!=0 && menuNumber == 0){
                ipDirection.pop_back();
            }
        }
        if (menuNumber == 0){
            ipLabel.setColor(sf::Color(73,183,108));
            startLabel.setColor(sf::Color::White);
        }
        else if(menuNumber==1){
            ipLabel.setColor(sf::Color::White);
            startLabel.setColor(sf::Color(73,183,108));
        }

        ipStatus.setString(ipDirection);

        window.clear();

        window.draw(backgroundSprite);
        window.draw(coliseumSprite);
        window.draw(titleLabel);
        window.draw(ipLabel);
        window.draw(ipStatus);
        window.draw(startLabel);

        window.display();
    }

}