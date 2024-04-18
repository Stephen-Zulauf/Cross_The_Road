#pragma once

#include "config.h"
#include "Tile.h"

class Land : public Tile {
private:

public:
	Land(float x, float y, float w, float h) :Tile(x, y, w, h, true,false) {
		//set fill color to green for testing
		//Data.setFillColor(sf::Color::White);
	}

	//draw to window
	void draw(sf::RenderWindow* nWindow) override {
		nWindow->draw(Data);
	}
};