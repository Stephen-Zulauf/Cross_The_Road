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
	Player(float x, float y, float w, float h, int startRow,int startCol, int tRows, Atlas* nAtlas) :Tile(x,y,w,h,true,false,false) {
		//set color to red for testing
		//Data.setFillColor(sf::Color(235, 89, 52, 255));

		this->row = startRow;
		this->col = startCol;
		this->totalRows = tRows;

		this->width = w;
		this->height = h;

		this->setPosition(width * (col - .5), height * ((totalRows-1)-row - .8));

		this->atlas = nAtlas;

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

	void updateLocation(int row, int col) {

		//set postion
		this->setPosition(width * (col - .5), height * ((totalRows - 1) - row - .8));
		
	}

};
