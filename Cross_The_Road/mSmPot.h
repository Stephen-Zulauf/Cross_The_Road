#pragma once

#include "SpriteAtlas.h"
#include "Tile.h"

class mSmPot : public Tile {
private:
	float offset = 0;

public:
	mSmPot(int nRow, int nCol, int tRows, float nW, float nH, Atlas* atlas)
		:Tile(nRow, nCol, tRows, nW, nH, true, false, true, atlas) {
		//set fill color to green for testing
		//Data.setFillColor(sf::Color::White);


		//set texture
		this->setTexture(atlas->getTileSet(4)->getTexture());
		this->setTexRec(atlas->getTileSet(4)->getTile(0, 4));

		//set random rotation
		int randt = rand() % 20;
		this->setRotation(randt);

		//compensate for rotation
		//this->setPosition(row, col, .1*(randt), 0);


	}

	//update sprites etc
	void updateXY(float xOffset, float yOffset) override {
		this->setPosition(this->row, this->col, xOffset, yOffset);
	}


	//draw to window
	void draw(sf::RenderWindow* nWindow) override {
		nWindow->draw(Data);
	}
};