#pragma once

#include "config.h"

class Tile {
private:
	//this containes postion.x postion.y and .color
	sf::RectangleShape Data;

public:
	//constructor
	Tile(float x, float y, float w, float h) {
		this->Data.setPosition(x, y);
		this->Data.setSize(sf::Vector2f(w, h));
		this->Data.setFillColor(sf::Color(x,y,w,255));
	}

	//draw to window
	void draw(sf::RenderWindow* nWindow) {
		nWindow->draw(Data);
	}

	//setters
	void setPosition(float x, float y) {
		this->Data.setPosition(x, y);
	}
	
	//getters
	sf::Vector2f getPosition() {
		return this->Data.getPosition();
	}

};
