#pragma once

#include "SpriteAtlas.h"
#include "Tile.h"

class LgStump : public Tile {
private:


public:
	LgStump(int nRow, int nCol, int tRows, float nW, float nH, Atlas* atlas)
		:Tile(nRow, nCol, tRows, nW, nH, false, false, false, atlas) {
		//set fill color to green for testing
		//Data.setFillColor(sf::Color::White);


		//set texture
		this->setTexture(atlas->getTileSet(2)->getTexture());
		this->setTexRec(atlas->getTileSet(2)->getTile(2, 4));

		updateLocation(nRow, nCol);

	}

	//this is needed to compensate for the scaling on the sprite
	void updateLocation(int row, int col) {

		//this->setPosition(width * (col - .5), height * ((totalRows-1)-row - .8));
		//(old offset reference)
		//set postion
		this->setPosition(row, col, 0, .2);

	}

	//draw to window
	void draw(sf::RenderWindow* nWindow) override {
		nWindow->draw(Data);

		updateLocation(this->row, this->col);
	}
};