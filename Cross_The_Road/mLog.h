#pragma once

//class for moving log tile.

#include "SpriteAtlas.h"
#include "Tile.h"

class mLog : public Tile {
private:

	float offset = 0;


public:
	mLog(int nRow, int nCol, int tRows, float nW, float nH, Atlas* atlas)
		:Tile(nRow, nCol, tRows, nW, nH, true, false, true, atlas) {
		//set fill color to green for testing
		//Data.setFillColor(sf::Color::White);

	
		//set texture
		this->setTexture(atlas->getTileSet(2)->getTexture());
		this->setTexRec(atlas->getTileSet(2)->getTile(2, 5));

		//set random rotation
		int randt = rand() % 3;
		this->setRotation(randt);

	}

	//update to move sprite over
	void update(float offset) override {
		this->setPosition(this->row, this->col, offset, 0);
	}

	//draw to window
	void draw(sf::RenderWindow* nWindow) override {
		nWindow->draw(Data);
		
	}
};
