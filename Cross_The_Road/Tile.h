#pragma once

#include "config.h"

class Tile {
protected:
	//this contains postion.x postion.y and .color
	sf::RectangleShape Data;

	//if the tile is walkable by the player or not
	bool walkable;

	//will the tile kill the player
	bool deadly;

	//movable (moves the player)
	bool mover;

	//keep track of location and demensions
	int row = 0;
	int col = 0;
	int totalRows = 0;
	float width = 0;
	float height = 0;

	//tall size sprite
	bool tall = false;

public:
	//constructor
	Tile(int nRow, int nCol, int tRows, float nW, float nH, bool isWalkable, bool isDeadly, bool isMover, Atlas* atlas) {
		this->row = nRow;
		this->col = nCol;
		this->totalRows = tRows;
		this->width = nW;
		this->height = nH;

		//t_width * i, t_height * ((rows - 1) - rowNum)
		this->Data.setPosition(width*col, height * ((totalRows-1)-row));
		this->Data.setSize(sf::Vector2f(width, height));
		this->walkable = isWalkable;
		this->deadly = isDeadly;
		this->mover = isMover;
		
	}

	//draw to window
	virtual void draw(sf::RenderWindow* nWindow) = 0;

	//update sprites etc
	virtual void update(float offset) {
		
	}

	//setters
	void setPosition(int nRow, int nCol, float xOff, float yOff) {
		this->Data.setPosition(width * (nCol - xOff), height * ((totalRows - 1) - nRow - yOff));
	}
	void setTexture(sf::Texture* nTexture) {
		this->Data.setTexture(nTexture);
	}
	void setTexRec(sf::IntRect nRect) {
		this->Data.setTextureRect(nRect);
	}
	void setSize(int rows, int cols) {
		this->Data.setSize(sf::Vector2f(width*cols, height*rows));
	}
	void setScale(float x, float y) {
		this->Data.setScale(sf::Vector2f(x, y));
	}
	void setRotation(float degrees) {
		this->Data.setRotation(degrees);
	}
	void decreaseRow() {
		this->row -= 1;
		this->Data.setPosition(width * col, height * ((totalRows - 1) - row));
	}
	
	//getters
	sf::Vector2f getPosition() {
		return this->Data.getPosition();
	}

	//check if walkable
	bool isWalkable() {
		return this->walkable;
	}

	//check if deadly
	bool isDeadly() {
		return this->deadly;
	}

	//check if moveable
	bool isMoving() {
		return this->mover;
	}

};
