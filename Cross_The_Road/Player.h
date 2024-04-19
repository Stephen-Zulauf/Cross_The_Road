#pragma once

#include "config.h"
#include "SpriteAtlas.h"
#include "Tile.h"

class Player : public Tile {
private:

	//current row and column of player
	int row = 0;
	int col = 0;

	//width and height of tile
	int width = 0;
	int height = 0;

	//reference to textures atlas to skin player
	Atlas* atlas = nullptr;

public:
	Player(float x, float y, float w, float h, int startRow,int startCol, Atlas* nAtlas) :Tile(x,y,w,h,true,false) {
		//set color to red for testing
		//Data.setFillColor(sf::Color(235, 89, 52, 255));

		this->row = startRow;
		this->col = startCol;

		this->width = w;
		this->height = h;

		this->setPosition(width * (col - .5), height * (row - .8));

		this->atlas = nAtlas;

		this->setTexture(atlas->getTileSet(3)->getTexture());
		sf::IntRect temp = atlas->getTileSet(3)->getTile(0, 0);
		//int scaler = 20;
		//temp.left += scaler;
		//temp.top -= scaler;
		//temp.width *= .8;
		//temp.height *= .8;
		this->setTexRec(temp);
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

	void updateLocation(int row, int col) {
		this->setPosition(width * (col - .5), height * (row - .8));
	}

	void moveUp() {
		this->setTexRec(atlas->getTileSet(3)->getTile(0, 1));
		row--;
		this->setPosition(width * (col - .5), height * (row - .8));
	}

	void moveLeft() {
		this->setTexRec(atlas->getTileSet(3)->getTile(0, 2));
		col--;
		this->setPosition(width * (col - .5), height * (row - .8));
	}

	void moveDown() {
		this->setTexRec(atlas->getTileSet(3)->getTile(0, 0));
		row++;
		this->setPosition(width * (col - .5), height * (row - .8));
	}

	void moveRight() {
		this->setTexRec(atlas->getTileSet(3)->getTile(0, 3));
		col++;
		this->setPosition(width * (col - .5), height * (row - .8));
	}
};
