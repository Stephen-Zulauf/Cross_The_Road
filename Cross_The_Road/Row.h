#pragma once

#include "config.h"
#include "TilesInclude.h"
#include "SpriteAtlas.h"
#include "TileContainer.h"

class Row {
private:

	//number of cols in row
	int cols = 0;
	//number of total rows
	int rows = 0;

	//row offset for drawing backwards
	int yOffset = 0;

	/*
	* row type
	* 0 = water
	* 1 = land
	*/
	int type = 0;

	//track direction if mover
	int direction = 0;
	//move tile type
	int mType = 0;
	//mover spacing
	int mSpace = 0;

	//tile width/height
	float t_width = 0;
	float t_height = 0;

	//row number
	int rowNum = 0;

	//pointer to sprite map to use for drawing
	Atlas* atlas = nullptr;

	//Tile containers
	std::vector<TileContainer*> Tiles;

public:
	Row(int nCols, int nType, int tWidth, int tHeight, int nRowNum, int nRows, Atlas* nAtlas) {
		cols = nCols;
		rows = nRows;
		

		type = nType;
		t_width = tWidth;
		t_height = tHeight;
		rowNum = nRowNum;
		atlas = nAtlas;
		direction = (rand() % 10) % 2;
		mType = rand() % 7;

		genContainers();
		genBase();
		genBridges();
		//genObsticals();
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

	void update() {

		//update movers
		if (type == 2) {
			genMovers();
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
			Tile* temp = new Water(rowNum, i, rows, t_width, t_height, atlas, 1);
			Tiles[i]->addTile(temp);
		}

		if (type == 1) {
			//generate land tiles and set textures
			for (int i = 0; i < cols; i++) {

				if (i == 0) {
					Tile* temp = new Grass(rowNum, i, rows, t_width, t_height, atlas, 0);
					Tiles[i]->addTile(temp);
				}
				else if (i == cols - 1) {
					Tile* temp = new Grass(rowNum, i, rows, t_width, t_height, atlas, 2);
					Tiles[i]->addTile(temp);
				}
				else {
					Tile* temp = new Grass(rowNum, i, rows, t_width, t_height, atlas, 1);
					Tiles[i]->addTile(temp);
				}
				
			}
		}
		else if (type == 2) {
			//generate movers and set textures
			for (int i = 0; i < cols; i++) {
				if (i % 2 == direction) {
					Tile* temp = new mLog(rowNum, i, rows, t_width, t_height, atlas);
					Tiles[i]->addTile(temp);
					/*switch (mType) {
					case 0:
						temp->setTexture(atlas->getTileSet(2)->getTexture());
						temp->setTexRec(atlas->getTileSet(2)->getTile(5, 2));
						Tiles[i]->addTile(temp);
						break;
					case 1:
						temp->setTexture(atlas->getTileSet(2)->getTexture());
						temp->setTexRec(atlas->getTileSet(2)->getTile(7, 3));
						Tiles[i]->addTile(temp);
						break;
					case 3:
						temp->setTexture(atlas->getTileSet(2)->getTexture());
						temp->setTexRec(atlas->getTileSet(2)->getTile(6, 2));
						Tiles[i]->addTile(temp);
						break;
					case 4:
						temp->setTexture(atlas->getTileSet(2)->getTexture());
						temp->setTexRec(atlas->getTileSet(2)->getTile(7, 4));
						Tiles[i]->addTile(temp);
						break;
					case 5:
						temp->setTexture(atlas->getTileSet(4)->getTexture());
						temp->setTexRec(atlas->getTileSet(4)->getTile(4, 0));
						Tiles[i]->addTile(temp);
						break;
					default:
						temp->setTexture(atlas->getTileSet(2)->getTexture());
						temp->setTexRec(atlas->getTileSet(2)->getTile(5, 2));
						Tiles[i]->addTile(temp);
						break;
					}*/
					
				}

			}
		}
		
	}

	//generate movables
	void genMovers() {

		//clear old ones
		for (int i = 0; i < cols; i++) {
			if (i % 2 == direction) {
				Tiles[i]->removeTile();
			}
		}

		//switch to odd or even row
		direction = !direction;

		//make new ones
		for (int i = 0; i < cols; i++) {
			if (i % 2 == direction) {
				Tile* temp = new mLog(rowNum, i, rows, t_width, t_height, atlas);
				Tiles[i]->addTile(temp);
				/*switch (mType) {
				case 0:
					temp->setTexture(atlas->getTileSet(2)->getTexture());
					temp->setTexRec(atlas->getTileSet(2)->getTile(5, 2));
					Tiles[i]->addTile(temp);
					break;
				case 1:
					temp->setTexture(atlas->getTileSet(2)->getTexture());
					temp->setTexRec(atlas->getTileSet(2)->getTile(7, 3));
					Tiles[i]->addTile(temp);
					break;
				case 3:
					temp->setTexture(atlas->getTileSet(2)->getTexture());
					temp->setTexRec(atlas->getTileSet(2)->getTile(6, 2));
					Tiles[i]->addTile(temp);
					break;
				case 4:
					temp->setTexture(atlas->getTileSet(2)->getTexture());
					temp->setTexRec(atlas->getTileSet(2)->getTile(7, 4));
					Tiles[i]->addTile(temp);
					break;
				case 5:
					temp->setTexture(atlas->getTileSet(4)->getTexture());
					temp->setTexRec(atlas->getTileSet(4)->getTile(4, 0));
					Tiles[i]->addTile(temp);
					break;
				default:
					temp->setTexture(atlas->getTileSet(2)->getTexture());
					temp->setTexRec(atlas->getTileSet(2)->getTile(5, 2));
					Tiles[i]->addTile(temp);
					break;
				}*/
			}

		}
		
	}

	//generate bridges (if water type)
	void genBridges() {
		if (type == 0) {

			for (int i = 0; i < cols; i++) {
				int type = rand() % 15;

				Tile* temp = new Log(rowNum, i, rows, t_width, t_height, atlas);
				Tiles[i]->addTile(temp);
				/*switch (type) {
				case 0:
					temp->setTexRec(atlas->getTileSet(2)->getTile(8, 4));
					Tiles[i]->addTile(temp);
					break;
				case 1:
					temp->setTexRec(atlas->getTileSet(2)->getTile(7, 4));
					Tiles[i]->addTile(temp);
					break;
				case 2:
					temp->setTexRec(atlas->getTileSet(2)->getTile(6, 4));
					Tiles[i]->addTile(temp);
					break;
				case 3:
					temp->setTexRec(atlas->getTileSet(2)->getTile(5, 4));
					Tiles[i]->addTile(temp);
					break;
				case 4:
					temp->setTexRec(atlas->getTileSet(2)->getTile(5, 2));
					Tiles[i]->addTile(temp);
					break;
				default:
					
					break;
				}
				std::cout << "creating bridge" << std::endl;*/
				
			}
		}
		
	}

	//generate obsticles (if land type)
	void genObsticals() {
		if (type == 1) {

			for (int i = 0; i < cols; i++) {
				int type = rand() % 20;
				//int chance = rand() % 10;

				Tile* temp = new RedMush(rowNum, i, rows, t_width, t_height, atlas);
				Tiles[i]->addTile(temp);
				
				/*switch (type) {
				case 0:
					temp->setTexRec(atlas->getTileSet(2)->getTile(5, 0));
					Tiles[i]->addTile(temp);
					break;
				case 1:
					temp->setTexRec(atlas->getTileSet(2)->getTile(4, 2));
					Tiles[i]->addTile(temp);
					break;
				case 2:
					temp->setTexRec(atlas->getTileSet(2)->getTile(7, 2));
					Tiles[i]->addTile(temp);
					break;
				default:

					break;
				}
				std::cout << "creating bridge" << std::endl;*/

			}
		}

	}

	bool checkWalkable(int col) {
		if (Tiles[col]->isWalkable()) {
			return true;
		}
		else {
			return false;
		}
	}

	bool checkDeath(int col) {
		if (Tiles[col]->isDeadly()) {
			return true;
		}
		else {
			return false;
		}
	}

	bool checkMovable(int col) {
		if (Tiles[col]->isMovable()) {
			return true;
		}
		else {
			return false;
		}
	}

	void increaseRow() {
		rowNum --;
		for (int i = 0; i < cols; i++) {
			Tiles[i]->decreaseRow();
		}
	}
};