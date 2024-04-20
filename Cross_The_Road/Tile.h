#pragma once

#include "config.h"

class Tile {
protected:
	//this containes postion.x postion.y and .color
	sf::RectangleShape Data;

	//if the tile is walkable by the player or not
	bool walkable;

	//will the tile kill the player
	bool deadly;

	//movable (moves the player)
	bool mover;

	//keep track of location and demensions
	float x = 0;
	float y = 0;
	float width = 0;
	float height = 0;

public:
	//constructor
	Tile(float nX, float nY, float nW, float nH, bool isWalkable, bool isDeadly, bool isMover) {
		this->x = nX;
		this->y = nY;
		this->width = nW;
		this->height = nH;

		this->Data.setPosition(x, y);
		this->Data.setSize(sf::Vector2f(width, height));
		this->walkable = isWalkable;
		this->deadly = isDeadly;
		this->mover = isMover;
		
	}

	//draw to window
	virtual void draw(sf::RenderWindow* nWindow) = 0;

	//setters
	void setPosition(float x, float y) {
		this->Data.setPosition(x, y);
	}
	void setTexture(sf::Texture* nTexture) {
		this->Data.setTexture(nTexture);
	}
	void setTexRec(sf::IntRect nRect) {
		this->Data.setTextureRect(nRect);
	}
	void setScale(float x, float y) {
		this->Data.setScale(sf::Vector2f(x, y));
	}
	void increaseRow() {
		this->y -= height;
		this->Data.setPosition(this->x, this->y);
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
