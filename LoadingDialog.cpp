//
// Created by joseph on 5/27/17.
//

#include "LoadingDialog.h"

LoadingDialog::LoadingDialog(sf::RenderWindow &window) : window(window) {
	rectangle.setSize(sf::Vector2f(9999, 9999));
	rectangle.setPosition(0,0);
	rectangle.setFillColor(sf::Color(0,0,0,150));
	
	
	subrectangle.setSize(sf::Vector2f(300,100));
	sf::FloatRect textRect = subrectangle.getLocalBounds();
	subrectangle.setOrigin(textRect.left + textRect.width/2.0f,
						   textRect.top  + textRect.height/2.0f);
	subrectangle.setPosition({ window.getSize().x/2.f, window.getSize().y/2.f });
	subrectangle.setFillColor(sf::Color(20,20,20,250));
	
	font.loadFromFile("Resources/CardsFont.TTF");
	
	
	loadingText.setFont(font);
	loadingText.setString("Loading");
	loadingText.setCharacterSize(15);
	sf::FloatRect textRect2 = loadingText.getLocalBounds();
	loadingText.setOrigin(textRect2.left + textRect2.width/2.0f,
						  textRect2.top  + textRect2.height/2.0f);
	loadingText.setPosition( {window.getSize().x/2.f, window.getSize().y/2.f - 25});
	loadingText.setColor(sf::Color::White);
	

	
	spinnerTexture.loadFromFile("Resources/spinner.png");
	spinner.setTexture(spinnerTexture);
	spinner.setScale(0.1,0.1);
	spinner.setOrigin(spinner.getPosition().x + spinnerTexture.getSize().x/2.0f,
					  spinner.getPosition().y  + spinnerTexture.getSize().y/2.0f);
	spinner.setPosition( {window.getSize().x/2.f, window.getSize().y/2.f + 15});
	
}

void LoadingDialog::draw() {
	if (showing) {
		window.draw(rectangle);
		window.draw(subrectangle);
		window.draw(spinner);
		window.draw(loadingText);
		
		spinner.setRotation(spinner.getRotation() + 1);
		
		if (spinner.getRotation() > 360) {
			spinner.setRotation(0);
		}
	}
}

bool LoadingDialog::isShowing() const {
	return showing;
}

void LoadingDialog::setShowing(bool showing) {
	LoadingDialog::showing = showing;
}

void LoadingDialog::show() {
	LoadingDialog::showing = true;
}


void LoadingDialog::hide() {
	LoadingDialog::showing = false;
}
