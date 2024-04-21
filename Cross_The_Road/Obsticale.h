#pragma once

#include "config.h"
#include "Tile.h"

class Obsticale : public Tile {
private:

public:
	Obsticale(float x, float y, float w, float h) :Tile(x, y, w, h, false, false, false) {
		//set fill color to brown for testing
		//Data.setFillColor(sf::Color(99, 53, 18, 255));
	}

	//draw to window
	void draw(sf::RenderWindow* nWindow) override {
		nWindow->draw(Data);
	}
};