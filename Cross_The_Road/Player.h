#pragma once

#include "config.h"
#include "Tile.h"

class Player : public Tile {
private:

	//current row and column of player
	int row = 0;
	int col = 0;

	//width and height of tile
	int width = 0;
	int height = 0;

public:
	Player(float x, float y, float w, float h, int startRow,int startCol) :Tile(x,y,w,h,true,false) {
		//set color to red for testing
		Data.setFillColor(sf::Color(235, 89, 52, 255));

		this->row = startRow;
		this->col = startCol;

		this->width = w;
		this->height = h;

		this->setPosition(width * startCol, height * row);

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
		this->setPosition(width * col, height * row);
	}

	void moveUp() {
		row--;
		this->setPosition(width * col, height * row);
	}

	void moveLeft() {
		col--;
		this->setPosition(width * col, height * row);
	}

	void moveDown() {
		row++;
		this->setPosition(width * col, height * row);
	}

	void moveRight() {
		col++;
		this->setPosition(width * col, height * row);
	}
};
