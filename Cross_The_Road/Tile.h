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

public:
	//constructor
	Tile(float x, float y, float w, float h, bool isWalkable, bool isDeadly, bool isMover) {
		this->Data.setPosition(x, y);
		this->Data.setSize(sf::Vector2f(w, h));
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
