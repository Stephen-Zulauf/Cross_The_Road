#pragma once

//class for moving log tile.

#include "config.h"
#include "Tile.h"

class mLog : public Tile {
private:
	//current location
	int col = 0;
	float elapsedMove = 0;

public:
	mLog(float x, float y, float w, float h) :Tile(x, y, w, h, true, false) {
		//set fill color to brown for testing
		//Data.setFillColor(sf::Color(99, 53, 18, 255));
	}

	//void update() override {

	//	//calculate current col
	//	elapsedMove += 5;
	//	if (elapsedMove >= 60) {
	//		col += 1;
	//		elapsedMove = 0;
	//	}
	//	//move to the right
	//	sf::Vector2f current = this->Data.getPosition();
	//	current.x += 5;
	//	this->Data.setPosition(current);
	//}

	//draw to window
	void draw(sf::RenderWindow* nWindow) override {
		nWindow->draw(Data);
	}
};