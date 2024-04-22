#pragma once

#include "SpriteAtlas.h"
#include "Tile.h"

class SmFlowerYell : public Tile {
private:


public:
	SmFlowerYell(int nRow, int nCol, int tRows, float nW, float nH, Atlas* atlas)
		:Tile(nRow, nCol, tRows, nW, nH, true, false, false, atlas) {
		//set fill color to green for testing
		//Data.setFillColor(sf::Color::White);


		//set texture
		this->setTexture(atlas->getTileSet(2)->getTexture());
		this->setTexRec(atlas->getTileSet(2)->getTile(2, 6));

	}

	//draw to window
	void draw(sf::RenderWindow* nWindow) override {
		nWindow->draw(Data);
	}
};
