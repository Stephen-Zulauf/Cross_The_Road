#pragma once

#include "SpriteAtlas.h"
#include "Tile.h"

class mSmFlowerYell : public Tile {
private:


public:
	mSmFlowerYell(int nRow, int nCol, int tRows, float nW, float nH, Atlas* atlas)
		:Tile(nRow, nCol, tRows, nW, nH, true, false, true, atlas) {
		//set fill color to green for testing
		//Data.setFillColor(sf::Color::White);


		//set texture
		this->setTexture(atlas->getTileSet(2)->getTexture());
		this->setTexRec(atlas->getTileSet(2)->getTile(2, 6));

		//set random rotation
		int randt = rand() % 5;
		this->setRotation(randt);

	}

	//draw to window
	void draw(sf::RenderWindow* nWindow) override {
		nWindow->draw(Data);
	}
};