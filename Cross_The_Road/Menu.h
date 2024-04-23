#pragma once

#include "config.h"

class Menu {

private:
	//window size
	float w_width;
	float w_height;

	//handle to draw window
	sf::RenderWindow* window;
	
	//menu elements
	sf::RectangleShape background;
	sf::RectangleShape menuBackground;
	sf::RectangleShape cursor;
	sf::RectangleShape scoreBox;

	//textures
	sf::Texture BGTexture; // just backgrounds
	sf::Texture UITexture; //(full sprite sheet)
	sf::Texture CurseText; //cursor

	//fonts
	sf::Font boldFont;
	sf::Font regFont;

	//text handle
	sf::Text text;

	//vec to keep track of mouse postion
	sf::Vector2i mPostion;

	//bools to keep track of quit and start
	bool display = true;
	bool quit = false;

	//keep track of score
	int score = 13928;


public:

	Menu(float wWidth, float wHeight, sf::RenderWindow* nWindow) {

		w_width = wWidth;
		w_height = wHeight;

		window = nWindow;

		//set cursor
		cursor.setPosition(sf::Vector2f(150, 150));
		cursor.setSize(sf::Vector2f(32, 32));
		if (!CurseText.loadFromFile("Cursor.png"))
		{
			std::cout << "ERR Menu: failed to load texture from file" << std::endl;
		}
		cursor.setTexture(&CurseText);
		cursor.setTextureRect(sf::IntRect(0, 0, 16, 16));

		//set background
		background.setPosition(sf::Vector2f(0, 0));
		background.setSize(sf::Vector2f(w_width, w_height));
		background.setFillColor(sf::Color(212, 172, 93, 75));

		//set menu background
		menuBackground.setPosition(sf::Vector2f(150, 50));
		menuBackground.setSize(sf::Vector2f(w_width-300, w_height-200));
		if (!BGTexture.loadFromFile("MenuBg.png"))
		{
			std::cout << "ERR Menu: failed to load texture from file" << std::endl;
		}
		menuBackground.setTexture(&BGTexture);
		menuBackground.setTextureRect(sf::IntRect(128, 0, 128, 144));
		
		//set scorebox
		scoreBox.setSize(sf::Vector2f(w_width/4, w_height/16));
		scoreBox.setPosition(sf::Vector2f(w_width - w_width / 4, 0));
		scoreBox.setTexture(&BGTexture);
		scoreBox.setTextureRect(sf::IntRect(128, 0, 128, 144));


		//load bold font
		if (!boldFont.loadFromFile("Silkscreen-Bold.ttf"))
		{
			std::cout << "ERR Menud: could not load font file" << std::endl;
		}

		//load reglar font
		if (!regFont.loadFromFile("Silkscreen-Regular.ttf"))
		{
			std::cout << "ERR Menud: could not load font file" << std::endl;
		}
	}

	void draw() {

		if (display == true) {
			//draw elements
			window->draw(background);
			window->draw(menuBackground);

			//draw text
			//header
			text.setFont(boldFont);
			text.setString("Cross The River");
			text.setCharacterSize(24);
			text.setFillColor(sf::Color(150, 109, 71));
			text.setPosition(sf::Vector2f(250, 120));
			window->draw(text);

			//update mouse postion
			mPostion = sf::Mouse::getPosition(*window);
			cursor.setPosition(sf::Vector2f(mPostion));

			//highlight text
			if (mPostion.x > 320 && mPostion.x < 420 && mPostion.y > 200 && mPostion.y < 250) {
				//start
				text.setFont(boldFont);
				text.setString("start");
				text.setCharacterSize(24);
				text.setFillColor(sf::Color(61, 44, 29));
				text.setPosition(sf::Vector2f(340, 200));
				window->draw(text);


			}
			else {
				//start
				text.setFont(boldFont);
				text.setString("start");
				text.setCharacterSize(24);
				text.setFillColor(sf::Color(150, 109, 71));
				text.setPosition(sf::Vector2f(340, 200));
				window->draw(text);
			}

			if (mPostion.x > 320 && mPostion.x < 420 && mPostion.y > 250 && mPostion.y < 300) {
				//quit
				text.setFont(boldFont);
				text.setString("quit");
				text.setCharacterSize(24);
				text.setFillColor(sf::Color(61, 44, 29));
				text.setPosition(sf::Vector2f(350, 250));
				window->draw(text);
			}
			else {
				//quit
				text.setFont(boldFont);
				text.setString("quit");
				text.setCharacterSize(24);
				text.setFillColor(sf::Color(150, 109, 71));
				text.setPosition(sf::Vector2f(350, 250));
				window->draw(text);
			}

			//check for mouse click
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (mPostion.x > 320 && mPostion.x < 420 && mPostion.y > 200 && mPostion.y < 250) {
					display = false;
					std::cout << "start" << std::endl;
				}
				else if (mPostion.x > 320 && mPostion.x < 420 && mPostion.y > 250 && mPostion.y < 300) {
					quit = true;
					std::cout << "quit" << std::endl;
				}

			}

			//draw cursor on top of everything
			window->draw(cursor);
		}
		else {
			//draw scorebox
			window->draw(scoreBox);

			//start
			text.setFont(regFont);
			text.setString(std::to_string(score));
			text.setCharacterSize(24);
			text.setFillColor(sf::Color(150, 109, 71));
			text.setPosition(sf::Vector2f(w_width - (w_width / 8)-50, 0));
			window->draw(text);

		}
		
	}

	//setters
	void reset() {
		this->display = true;
		this->quit = false;
	}

	void setDisplay(bool isDisplayed) {
		this->display = isDisplayed;
	}

	void updateScore(int nScore) {
		this->score = nScore;
	}

	//getters
	bool getDisplay() {
		return this->display;
	}
	bool getQuit() {
		return this->quit;
	}

};