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

		player = new Player(0, 0, tileSize.x, tileSize.y, location.y, location.x, gridSize.y, atlas);

		std::cout << "start row:" << location.y << std::endl;
		std::cout << "start col:" << location.x << std::endl;
	}
	~PlayerLogic() {
		delete player;
	}

	//request the player moves
	void moveRequest(int nDirection) {
		direction = nDirection;
	}

	//player movement
	//void moveplayer(int nDirection)
	//{
	//	//need to reset move direction to -1
	//	switch (nDirection) {
	//	case 0:
	//		//move player up
	//		if (checkCollision(player->getRow() + 1, player->getCol()) == false) {
	//			player->moveUp();
	//			std::cout << "player move up" << std::endl;
	//		}
	//		else {
	//			std::cout << "player colision" << std::endl;
	//		}

	//		//check if dead
	//		if (checkDeath(player->getRow(), player->getCol()) == true) {
	//			this->dead = true;
	//			std::cout << "DEAD" << std::endl;
	//		}

	//		break;
	//	case 1:
	//		//move player left
	//		if (checkCollision(player->getRow(), player->getCol() - 1) == false) {
	//			player->moveLeft();
	//			std::cout << "player move left" << std::endl;
	//		}
	//		else {
	//			std::cout << "player colision" << std::endl;
	//		}

	//		//check if dead
	//		if (checkDeath(player->getRow(), player->getCol()) == true) {
	//			this->dead = true;
	//			std::cout << "DEAD" << std::endl;
	//		}

	//		break;
	//	case 2:
	//		//move player down
	//		if (checkCollision(player->getRow() - 1, player->getCol()) == false) {
	//			player->moveDown();
	//			std::cout << "player move down" << std::endl;
	//		}
	//		else {
	//			std::cout << "player colision" << std::endl;
	//		}

	//		//check if dead
	//		if (checkDeath(player->getRow(), player->getCol()) == true) {
	//			this->dead = true;
	//			std::cout << "DEAD" << std::endl;
	//		}

	//		break;
	//	case 3:
	//		//move player right
	//		if (checkCollision(player->getRow(), player->getCol() + 1) == false) {
	//			player->moveRight();
	//			std::cout << "player move right" << std::endl;
	//		}
	//		else {
	//			std::cout << "player colision" << std::endl;
	//		}

	//		//check if dead
	//		if (checkDeath(player->getRow(), player->getCol()) == true) {
	//			this->dead = true;
	//			std::cout << "DEAD" << std::endl;
	//		}

	//		break;
	//	default:
	//		break;
	//	}

	//}

	//logic loop
	//returns if dead to check in main and reset grid
	//returns true if player died
	void loop() {

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

			//check if on a moving tile
			if (mGrid->checkMovable(location.y, location.x)) {
				//TODO check direction of moving row here
				//move player left for now
				//change location
				location.x += 1;
				player->updateLocation(location.y, location.x);
			}

		}
		else {
			//tell grid player died
			mGrid->isDead(true);

			//reset player location
			location.x = gridSize.x / 2;
			location.y = 0;
			player->updateLocation(location.y, location.x);
		}

		std::cout << "player row " << player->getRow() << std::endl;
		std::cout << "player col " << player->getCol() << std::endl;
		player->draw(window);
	}
};