#pragma once

#include "config.h"
#include "Player.h"
#include "Grid.h"

class PlayerLogic {

private:
	//player tile
	Player* player = nullptr;

	//reference to grid
	Grid* mGrid = nullptr;

	//reference to atlas
	Atlas* atlas = nullptr;

	//window handle
	sf::RenderWindow* window = nullptr;

	//x columns, y rows
	sf::Vector2i gridSize;

	//x column, y row
	sf::Vector2i location;

	//x width, y height
	sf::Vector2f tileSize;

	//request to move player
	int direction = -1;

	//track if on movable tile
	bool mover = false;

	//Keep track of time from loop and update function
	bool update = false;
	int scroll = 0;

public:

	PlayerLogic(Grid* nGrid, Atlas* nAtlas, sf::RenderWindow* nWindow) {

		//set reference to grid
		mGrid = nGrid;

		//get reference to atlas
		atlas = nAtlas;

		//get reference to window
		window = nWindow;

		//get total size of grid
		gridSize = mGrid->getSize();

		//set start location of player
		location.x = gridSize.x / 2;
		location.y = 0;

		//set tile size
		tileSize = mGrid->getTileSize();

		player = new Player(location.y,location.x,gridSize.y,tileSize.x,tileSize.y,atlas);

		std::cout << "start row:" << location.y << std::endl;
		std::cout << "start col:" << location.x << std::endl;
	}
	~PlayerLogic() {
		delete player;
	}

	//get player for drawing
	Player* getPlayer() {
		return this->player;
	}

	//request the player moves
	void moveRequest(int nDirection) {
		direction = nDirection;
	}

	//logic loop
	//returns if dead to check in main and reset grid
	//returns true if player died
	void loop(bool isUpdate, bool removal, bool* dead) {

		//move with the grid
		if (isUpdate) {
			
			if (mover) {
				//change location
				location.x -= 1;
				player->updateLocation(location.y, location.x);
			}
		}

		//if row removed
		if (removal) {
			//change location
			location.y -= 1;
			player->updateLocation(location.y, location.x);
		}

		//check if dead
		if (mGrid->checkDeath(location.y, location.x) == false) {

			//check for movement request
			if (direction >= 0) {

				//check for collison
				switch (direction) {
				//up
				case 0:
					if (mGrid->checkWalkable(location.y + 1, location.x)) {
						//change location
						location.y += 1;
						player->updateLocation(location.y,location.x);
					}
					
					//reset move request
					direction = -1;

					std::cout << "player move up" << std::endl;
					break;
				//left
				case 1:
					if (mGrid->checkWalkable(location.y, location.x - 1)) {
						//change location
						location.x -= 1;
						player->updateLocation(location.y, location.x);
					}

					//reset move request
					direction = -1;

					std::cout << "player move left" << std::endl;
					break;
				//down
				case 2:
					if (mGrid->checkWalkable(location.y - 1, location.x)) {
						//change location
						location.y -= 1;
						player->updateLocation(location.y, location.x);
					}

					//reset move request
					direction = -1;

					std::cout << "player move down" << std::endl;
					break;
				//right
				case 3:
					if (mGrid->checkWalkable(location.y, location.x + 1)) {
						//change location
						location.x += 1;
						player->updateLocation(location.y, location.x);
					}
					
					//reset move request
					direction = -1;

					std::cout << "player move right" << std::endl;
					break;

				}
				
			}
			//check if on moving tile
			if (mGrid->checkMovable(location.y, location.x)) {
				mover = true;
				//std::cout << "mover" << std::endl;
			}
			else {
				mover = false;
			}

		}
		else {
			//tell grid player died
			mGrid->isDead(true);
			//tell master clock player died
			*dead = true;

			//reset player location
			location.x = gridSize.x / 2;
			location.y = 0;
			player->updateLocation(location.y, location.x);

			scroll = 0;
		}

	}
};