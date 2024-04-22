#pragma once

#include "config.h"
#include "SpriteAtlas.h"
#include "Tile.h"

class Water : public Tile {
private:
	//pos: 0 left-end, 1 middle-left, 2 middle-right, 3 right-end 
	int pos = 0;

public:
	Water(int nRow, int nCol, int tRows, float nW, float nH, Atlas* atlas, int nPos)
		:Tile(nRow, nCol, tRows, nW, nH, true, true, false, atlas) {
		//set fill color to green for testing
		//Data.setFillColor(sf::Color::White);

		//set texture
		pos = nPos;

		this->setTexture(atlas->getTileSet(0)->getTexture());

		switch (pos) {
		case 0:
			//left end
			this->setTexRec(atlas->getTileSet(0)->getTile(0, 0));
			break;
		case 1:
			//middle-left
			this->setTexRec(atlas->getTileSet(0)->getTile(0, 1));
			break;
		case 2:
			//middle-right
			this->setTexRec(atlas->getTileSet(0)->getTile(0, 2));
			break;
		case 3:
			//right-end
			this->setTexRec(atlas->getTileSet(0)->getTile(0, 3));
			break;
		default:
			//middle-left
			this->setTexRec(atlas->getTileSet(0)->getTile(0, 1));
			break;
		}

	}

	//draw to window
	void draw(sf::RenderWindow* nWindow) override {
		nWindow->draw(Data);
	}
};