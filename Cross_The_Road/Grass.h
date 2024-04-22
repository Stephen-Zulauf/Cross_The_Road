#pragma once

#include "SpriteAtlas.h"
#include "Tile.h"

class Grass : public Tile {
private:
	//pos: 0 left-end, 1 middle, 2 right-end
	int pos = 0;

public:
	Grass(int nRow, int nCol, int tRows, float nW, float nH, Atlas* atlas, int nPos) 
		:Tile(nRow, nCol, tRows, nW, nH, true, false, false, atlas) {
		//set fill color to green for testing
		//Data.setFillColor(sf::Color::White);

		//set texture
		pos = nPos;

		this->setTexture(atlas->getTileSet(1)->getTexture());
		
		switch (pos) {
		case 0:
			//left end
			this->setTexRec(atlas->getTileSet(1)->getTile(3, 0));
			break;
		case 1:
			//middle
			this->setTexRec(atlas->getTileSet(1)->getTile(3, 1));
			break;
		case 2:
			//right-end
			this->setTexRec(atlas->getTileSet(1)->getTile(3, 2));
			break;
		}

	}

	//draw to window
	void draw(sf::RenderWindow* nWindow) override {
		nWindow->draw(Data);
	}
};
