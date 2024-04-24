#pragma once

#include "config.h"
#include "SpriteAtlas.h"
#include "Tile.h"

class Player : public Tile {
private:

	//current row and column of player
	int row = 0;
	int col = 0;

	//total rows
	int totalRows = 0;

	//width and height of tile
	int width = 0;
	int height = 0;

	//reference to textures atlas to skin player
	Atlas* atlas = nullptr;

public:
	Player(int nRow, int nCol, int tRows, float nW, float nH, Atlas* atlas) 
		:Tile(nRow, nCol, tRows, nW, nH, true, false, false, atlas) {
		//set color to red for testing
		//Data.setFillColor(sf::Color(235, 89, 52, 255));

		this->row = nRow;
		this->col = nCol;
		this->totalRows = tRows;

		this->width = nW;
		this->height = nH;

		//this->setPosition(width * (col - .5), height * ((totalRows-1)-row - .8));

		//update location with scale offset
		updateLocation(row, col,0,0);

		this->atlas = atlas;

		this->setTexture(atlas->getTileSet(3)->getTexture());
		this->setTexRec(atlas->getTileSet(3)->getTile(0, 0));
		this->setScale(2, 2);

	}
	//draw to window
	void draw(sf::RenderWindow* nWindow) override{
		nWindow->draw(Data);
	}

	int getRow() {
		return this->row;
	}
	int getCol() {
		return this->col;
	}

	void updateTexture(int direction, int cycle) {
		this->setTexRec(atlas->getTileSet(3)->getTile(direction, cycle));
	}

	//this is needed to compensate for the scaling on the sprite
	void updateLocation(int row, int col, float xOffset, float yOffset) {

		//this->setPosition(width * (col - .5), height * ((totalRows-1)-row - .8));
		//(old offset reference)
		//set postion
		this->setPosition(row,col, xOffset + .5, yOffset + .8);
		
	}

};
