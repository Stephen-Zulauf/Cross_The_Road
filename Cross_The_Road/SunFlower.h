#pragma once

#include "SpriteAtlas.h"
#include "Tile.h"

class Sunflower : public Tile {
private:


public:
	Sunflower(int nRow, int nCol, int tRows, float nW, float nH, Atlas* atlas)
		:Tile(nRow, nCol, tRows, nW, nH, false, false, false, atlas) {
		//set fill color to green for testing
		//Data.setFillColor(sf::Color::White);

		//set larger size
		this->setSize(2, 1);

		//set texture
		this->setTexture(atlas->getTileSet(2)->getTexture());
		this->setTexRec(atlas->getTileSet(2)->getTile(2, 8, 2));

		updateLocation(nRow, nCol);
	}

	//this is needed to compensate for the scaling on the sprite
	void updateLocation(int row, int col) {

		//set postion
		this->setPosition(row, col, 0, 1.2);

	}

	//update sprites etc
	void updateXY(float xOffset, float yOffset) override {
		this->setPosition(this->row, this->col, 0, yOffset+1.2);
	}

	//draw to window
	void draw(sf::RenderWindow* nWindow) override {
		nWindow->draw(Data);

		updateLocation(this->row, this->col);

	}
};