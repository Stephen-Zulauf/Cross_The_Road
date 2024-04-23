#pragma once

#include "config.h"

class Menu {

private:
	//window size
	float w_width;
	float w_height;

	sf::RenderWindow* window;
	
	sf::RectangleShape background;
	sf::RectangleShape menuBackground;

	sf::RectangleShape button;

	sf::Font font;

	sf::Text text;

	sf::Texture bgTexture;

public:

	Menu(float wWidth, float wHeight, sf::RenderWindow* nWindow) {

		w_width = wWidth;
		w_height = wHeight;

		window = nWindow;

		//set background
		background.setPosition(sf::Vector2f(0, 0));
		background.setSize(sf::Vector2f(w_width, w_height));
		background.setFillColor(sf::Color(212, 172, 93, 75));

		//set menu background
		menuBackground.setPosition(sf::Vector2f(150, 100));
		menuBackground.setSize(sf::Vector2f(w_width-300, w_height-200));
		//menuBackground.setFillColor(sf::Color(212, 93, 93));
		if (!bgTexture.loadFromFile("MenuBG.png"))
		{
			std::cout << "ERR Menu: failed to load texture from file"  << std::endl;
		}
		menuBackground.setTexture(&bgTexture);
		menuBackground.setTextureRect(sf::IntRect(128,0,w_width-300, w_height-200));
		menuBackground.setScale(sf::Vector2f(4, 3));


		/*if (!font.loadFromFile("arial.ttf"))
		{
			std::cout << "ERR Menud: could not load font file" << std::endl;
		}*/
	}

	void draw() {
		window->draw(background);
		window->draw(menuBackground);
	}

};