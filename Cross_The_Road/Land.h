#pragma once

#include "config.h"
#include "Tile.h"

class Land : public Tile {
private:
	//can player stand on it?
	bool walkable = true;

public:
	Land(float x, float y, float w, float h) :Tile(x, y, w, h) {
		//set fill color to green for testing
		Data.setFillColor(sf::Color(58, 235, 52, 255));
	}

	//draw to window
	void draw(sf::RenderWindow* nWindow) override {
		nWindow->draw(Data);
	}
};