#pragma once

#include "SpriteAtlas.h"
#include "Tile.h"

class mApple : public Tile {
private:
	float offset = 0;

public:
	mApple(int nRow, int nCol, int tRows, float nW, float nH, Atlas* atlas)
		:Tile(nRow, nCol, tRows, nW, nH, true, false, true, atlas) {
		//set fill color to green for testing
		//Data.setFillColor(sf::Color::White);


		//set texture
		this->setTexture(atlas->getTileSet(2)->getTexture());
		this->setTexRec(atlas->getTileSet(2)->getTile(2, 1));

		//set random rotation
		int randt = rand() % 20;
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