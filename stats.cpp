//
// Created by danielc on 26/05/17.
//

#include "stats.h"
#include <iostream>
#define SIZE 28
stats::stats(){
    font.loadFromFile("Resources/CardsFont.TTF");

    Gen.setFont(font);
    Gen.setCharacterSize(SIZE);
    Gen.setColor(sf::Color::White);
    Gen.setPosition(10,10);


    Time.setFont(font);
    Time.setCharacterSize(SIZE);
    Time.setColor(sf::Color::White);
    Time.setPosition(10,50);

    Gladiador.setFont(font);
    Gladiador.setCharacterSize(SIZE);
    Gladiador.setColor(sf::Color::White);
    Gladiador.setPosition(1150,10);

    Vida.setFont(font);
    Vida.setCharacterSize(SIZE);
    Vida.setColor(sf::Color::White);
    Vida.setPosition(1150,50);

    Fitness.setFont(font);
    Fitness.setCharacterSize(SIZE);
    Fitness.setColor(sf::Color::White);
    Fitness.setPosition(1150,90);

    Kills.setFont(font);
    Kills.setCharacterSize(SIZE);
    Kills.setColor(sf::Color::White);
    Kills.setPosition(1150,130);

}

void stats::update_gen_stats(sf::RenderWindow &window, int numero_generacion, int tiempo_restante) {
    std::string generacion= "Generacion actual: "+std::to_string(numero_generacion);
    std::string tiempo="Tiempo restante: "+std::to_string(tiempo_restante);
    Gen.setString(generacion);
    Time.setString(tiempo);

    window.draw(Gen);
    window.draw(Time);


}
void stats::update_gladiator_stats(sf::RenderWindow &window, Gladiator &gladiator) {
    std::string glad_nombre="Mejor Gladiador: "+std::to_string(0);
    std::string glad_vida="Vida: "+std::to_string(0);
    std::string glad_fitness="Fitness: "+std::to_string(0);
    std::string glad_kills="Eliminaciones: "+std::to_string(0);

    Gladiador.setString(glad_nombre);
    Vida.setString(glad_vida);
    Fitness.setString(glad_fitness);
    Kills.setString(glad_kills);

    window.draw(Gladiador);
    window.draw(Vida);
    window.draw(Fitness);
    window.draw(Kills);
}