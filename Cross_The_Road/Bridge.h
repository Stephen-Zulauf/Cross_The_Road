#pragma once

#include "config.h"
#include "Tile.h"

class Bridge : public Tile {
private:

public:
	Bridge(float x, float y, float w, float h) :Tile(x, y, w, h, true, false,false) {
		//set fill color to brown for testing
		//Data.setFillColor(sf::Color(99, 53, 18, 255));
	}

	//draw to window
	void draw(sf::RenderWindow* nWindow) override {
		nWindow->draw(Data);
	}
};