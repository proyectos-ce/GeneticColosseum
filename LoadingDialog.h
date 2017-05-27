//
// Created by joseph on 5/27/17.
//

#ifndef GENETICCOLOSSEUM_LOADINGDIALOG_H
#define GENETICCOLOSSEUM_LOADINGDIALOG_H


#include <SFML/Graphics.hpp>

class LoadingDialog {
private:
	
	sf::Sprite spinner;
	sf::Texture spinnerTexture;
	sf::Text loadingText;
	sf::RectangleShape subrectangle;
	sf::RectangleShape rectangle;
	sf::Font font;
	
	
	sf::RenderWindow &window;
	bool showing = true;
public:
	bool isShowing() const;
	
	void setShowing(bool showing);
	
	LoadingDialog(sf::RenderWindow &window);
	
	void draw();
	
	void hide();
	
	void show();
};


#endif //GENETICCOLOSSEUM_LOADINGDIALOG_H
