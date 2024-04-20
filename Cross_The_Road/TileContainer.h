#pragma once

#include "config.h"
#include "Tile.h"

class TileContainer {
private:
	std::vector<Tile*> Tiles;

public:
	~TileContainer() {
		for (int i = 0; i < Tiles.size(); i++) {
			delete Tiles[i];
			Tiles.clear();
		}
	}

	void addTile(Tile* nTile) {
		Tiles.push_back(nTile);
	}

	void removeTile() {
		delete Tiles.back();
		Tiles.pop_back();
	}

	std::vector<Tile*> getTiles() {
		return this->Tiles;
	}

	bool isWalkable() {
		return Tiles.back()->isWalkable();
	}

	bool isDeadly() {
		return Tiles.back()->isDeadly();
	}

	bool isMovable() {
		return Tiles.back()->isMoving();
	}

	void increaseRow() {
		for (int i = 0; i < Tiles.size(); i++) {
			Tiles[i]->increaseRow();
		}
	}

	void drawTiles(sf::RenderWindow* window) {
		for (int i = 0; i < Tiles.size(); i++) {
			Tiles[i]->draw(window);
		}
	}
};