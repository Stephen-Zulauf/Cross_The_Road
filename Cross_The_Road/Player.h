#pragma once

#include "config.h"
#include "Tile.h"

class Player : public Tile {
private:

public:
	Player(float x, float y, float w, float h) :Tile(x,y,w,h) {
		//set color to red for testing
		Data.setFillColor(sf::Color(235, 89, 52, 255));
	}
	//draw to window
	void draw(sf::RenderWindow* nWindow) override{
		nWindow->draw(Data);
	}
};
