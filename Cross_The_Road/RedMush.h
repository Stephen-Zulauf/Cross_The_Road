#pragma once

#include "config.h"
#include "SpriteAtlas.h"
#include "Tile.h"

class RedMush : public Tile {
private:


public:
	RedMush(int nRow, int nCol, int tRows, float nW, float nH, Atlas* atlas)
		:Tile(nRow, nCol, tRows, nW, nH, false, false, false, atlas) {
		//set fill color to green for testing
		//Data.setFillColor(sf::Color::White);


		//set texture
		this->setTexture(atlas->getTileSet(2)->getTexture());
		this->setTexRec(atlas->getTileSet(2)->getTile(6, 0));

	}

	//draw to window
	void draw(sf::RenderWindow* nWindow) override {
		nWindow->draw(Data);
	}
};