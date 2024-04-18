#pragma once

#include "config.h"
#include "Land.h"
#include "Water.h"
#include "Player.h"
#include "Bridge.h"
#include "SpriteAtlas.h"
#include "TileContainer.h"

class Row {
private:

	//number of cols in row
	int cols = 0;

	/*
	* row type
	* 0 = water
	* 1 = land
	*/
	int type = 0;

	//tile width/height
	float t_width = 0;
	float t_height = 0;

	//row number
	int rowNum = 0;

	//is player on this row
	bool player = false;

	//pointer to sprite map to use for drawing
	Atlas* atlas = nullptr;

	//Tile containers
	std::vector<TileContainer*> Tiles;

public:
	Row(int nCols, int nType, int tWidth, int tHeight, int nRowNum, bool nPlayer, Atlas* nAtlas) {
		cols = nCols;
		type = nType;
		t_width = tWidth;
		t_height = tHeight;
		rowNum = nRowNum;
		player = nPlayer;
		atlas = nAtlas;

		genContainers();
		genBase();
	}
	Row(Row& copy) {

	}
	~Row() {
		for (int i = 0; i < Tiles.size(); i++) {
			delete Tiles[i];
		}
	}

	void draw(sf::RenderWindow* window) {

		for (int i = 0; i < Tiles.size(); i++) {
			Tiles[i]->drawTiles(window);
		}
	}

	void update(int playerPos) {
		if (playerPos > 0) {
			player = true;
			for (int i = 0; i < playerPos; i++) {
				if (Tiles[i]->getTiles().size() > 2) {
					Tiles[i]->removeTile();
				}
			}
			Tiles[playerPos]->addTile(new Player(t_width * playerPos, t_height * rowNum, t_width, t_height));
		}
	}

	//generate tile containers
	void genContainers() {
		for (int i = 0; i < cols; i++) {
			Tiles.push_back(new TileContainer());
		}
	}

	//generate tiles for base tile type
	void genBase() {
		
		//water underneath everything
		for (int i = 0; i < cols; i++) {
			Tile* temp = new Water(t_width * i, t_height * rowNum, t_width, t_height);
			temp->setTexture(atlas->getTileSet(0)->getTexture());
			temp->setTexRec(atlas->getTileSet(0)->getTile(0, 0));
			Tiles[i]->addTile(temp);
		}

		if (type == 1) {
			for (int i = 0; i < cols; i++) {
				Tile* temp = new Land(t_width * i, t_height * rowNum, t_width, t_height);
				if (i == 0) {
					temp->setTexture(atlas->getTileSet(1)->getTexture());
					temp->setTexRec(atlas->getTileSet(1)->getTile(0, 3));
					Tiles[i]->addTile(temp);
				}
				else if (i == cols - 1) {
					temp->setTexture(atlas->getTileSet(1)->getTexture());
					temp->setTexRec(atlas->getTileSet(1)->getTile(2, 3));
					Tiles[i]->addTile(temp);
				}
				else {
					temp->setTexture(atlas->getTileSet(1)->getTexture());
					temp->setTexRec(atlas->getTileSet(1)->getTile(1, 3));
					Tiles[i]->addTile(temp);
				}
				
			}
		}
		
	}

	//generate tiles for obstacles
	void genObstacles() {
		for (int i = 0; i < cols; i++) {
			Tile* temp = new Land(t_width * i, t_height * rowNum, t_width, t_height);
			Tiles[i]->addTile(temp);
		}
	}

	//generate movables
	void genMovers() {
		for (int i = 0; i < cols; i++) {
			Tile* temp = new Land(t_width * i, t_height * rowNum, t_width, t_height);
			Tiles[i]->addTile(temp);
		}
	}

	//generate bridges (if water type)
	void genBridges() {
		for (int i = 0; i < cols; i++) {
			Tile* temp = new Land(t_width * i, t_height * rowNum, t_width, t_height);
			Tiles[i]->addTile(temp);
		}
	}
};