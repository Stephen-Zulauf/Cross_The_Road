#pragma once

#include "config.h"
#include "Row.h"

class Grid {
private:

	//handle to window created by sfml so we can draw on it
	sf::RenderWindow* window = nullptr;

	//rows and columns in grid.
	int rows = 0;
	int columns = 0;
  
	//width and height of each tile in grid
	float t_width = 0;
	float t_height = 0;

	//keep track of player location
	Player* player = nullptr;
	//track if player is dead
	bool dead = false;

	//vector of rows
	std::vector<Row*> Rows;

	//add sprite atlas
	Atlas* atlas = nullptr;

	//Keep track of time from loop and update function
	float elaTime = 0.0f;

public:
	//constructor
	Grid(int nRows, int nColumns, float w_width, float w_height, sf::RenderWindow* nWindow) 
	{
		
		//set window
		window = nWindow;

		//set rows and columns
		rows = nRows;
		columns = nColumns;

		//determine width/height of tiles from screen width/height of window
		t_width = w_width / columns;
		t_height = w_height / rows;

		//load tile sets
		atlas = new Atlas;

		initGrid();

		//init player
		this->player = new Player(0, 0, t_width,t_height, rows-1, floor(columns / 2), atlas);

	}
	
	//destructor
	~Grid() {
		for (int i = 0; i < Rows.size(); i++) {
			delete Rows[i];
		}
		Rows.clear();
	}

	//This function resets the grid to its intital state;
	//it uses random numbers to generate water or land
	//for each row in the grid
	void initGrid() {

		//keep track of last row type created
		int last = 1;

		//for each row
		for (int i = 0; i < rows; i++) {

			//check if we are generating top or bottom row
			//so the top and bottom row will always be land
			//at the start

			if (i > 0 && i != rows - 1) {

				//select random row type
				int type = 0 + (int)(rand() / (double)(RAND_MAX + 1) * (10 - 0 + 1));

				//if last row created was water 
				// create a 2 row (mover)
				if (last == 0) {
					last = 2;
					Rows.push_back(new Row(columns, 2, t_width, t_height, i, atlas));
				}
				//create a 0 row (water)
				else if(type < 5) {
					last = 0;
					Rows.push_back(new Row(columns, 0, t_width, t_height, i, atlas));
				}
				//create a 1 type row (land)
				else {
					last = 1;
					Rows.push_back(new Row(columns, 1, t_width, t_height, i, atlas));
				}

			}
			//create a 1 type row (land)
			else {
				Rows.push_back(new Row(columns, 1, t_width, t_height, i, atlas));
			}

		}

	}

	//draw each tile in Tiles vector
	void drawGrid() {

		//call update elasped time
		update();

		//draw rows
		for (int i = 0; i < Rows.size(); i++) {

			Rows[i]->draw(window);
		}

		player->draw(window);
	}

	//update moving tiles etc.
	void update() {

		//increase ellapsed time
		elaTime++;

		//update rows
		for (int i = 0; i < Rows.size(); i++) {

			Rows[i]->update(elaTime);
			
		}

		//check if player is on movable tile and move them
		if (checkMovable(player->getRow(), player->getCol()-1) == true && elaTime == 60) {
			if (checkCollision(player->getRow(), player->getCol() - 1) == false) {
				player->moveLeft();
				std::cout << "player move left" << std::endl;
			}
		}

		//reset
		if (elaTime > 60) {
			elaTime = 0;
		}

	}

	//check for player collison before moving
	//returns true if collison
	bool checkCollision(int row, int col) {
		if (row < this->rows && row >= 0) {
			if (col < this->columns && col >= 0) {
				if (this->Rows[row]->checkMovable(col) == true) {
						return false;
				}
			}
		}
		else {
			return true;
		}
	}

	//check if players dead after move
	//returns true if dead
	bool checkDeath(int row, int col) {
		if (this->Rows[row]->checkDeath(col) == true) {
			return true;
		}
		else {
			return false;
		}
	}

	//check if players on a movable tile after move
	//returns true if movable
	bool checkMovable(int row, int col) {
		if (this->Rows[row]->checkMovable(col) == true) {
			return true;
		}
		else {
			return false;
		}
	}

	void setplayer(Player n)
	{
		this->player = &n;
	}

	void moveplayer(int direction)
	{
		switch (direction) {
		case 0:
			//move player up
			if (checkCollision(player->getRow() - 1, player->getCol()) == false) {
				player->moveUp();
				std::cout << "player move up" << std::endl;
			}
			else {
				std::cout << "player colision" << std::endl;
			}
			
			//check if dead
			if (checkDeath(player->getRow(), player->getCol()) == true) {
				this->dead = true;
				std::cout << "DEAD" << std::endl;
			}
			
			break;
		case 1:
			//move player left
			if (checkCollision(player->getRow(), player->getCol()-1) == false) {
				player->moveLeft();
				std::cout << "player move left" << std::endl;
			}
			else {
				std::cout << "player colision" << std::endl;
			}

			//check if dead
			if (checkDeath(player->getRow(), player->getCol()) == true) {
				std::cout << "DEAD" << std::endl;
				this->dead = true;
			}
			
			break;
		case 2:
			//move player down
			if (checkCollision(player->getRow()+1, player->getCol()) == false) {
				player->moveDown();
				std::cout << "player move down" << std::endl;
			}
			else {
				std::cout << "player colision" << std::endl;
			}

			//check if dead
			if (checkDeath(player->getRow(), player->getCol()) == true) {
				std::cout << "DEAD" << std::endl;
				this->dead = true;
			}

			break;
		case 3:
			//move player right
			if (checkCollision(player->getRow(), player->getCol()+1) == false) {
				player->moveRight();
				std::cout << "player move right" << std::endl;
			}
			else {
				std::cout << "player colision" << std::endl;
			}

			//check if dead
			if (checkDeath(player->getRow(), player->getCol()) == true) {
				std::cout << "DEAD" << std::endl;
				this->dead = true;
			}

			break;
		default:
			break;
		}
		
	}

};

