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

	//keep track of scrolling
	int scroll = 0;

	//keep track of rows buffer
	int addedRows = 0;

	//keep track of last row type created
	int last = 1;

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
		this->player = new Player(0, 0, t_width,t_height, 0, floor(columns / 2), rows, atlas);

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
					Rows.push_back(new Row(columns, 2, t_width, t_height, i, rows, atlas));
				}
				//create a 0 row (water)
				else if(type < 5) {
					last = 0;
					Rows.push_back(new Row(columns, 0, t_width, t_height, i, rows, atlas));
				}
				//create a 1 type row (land)
				else {
					last = 1;
					Rows.push_back(new Row(columns, 1, t_width, t_height, i, rows, atlas));
				}

			}
			//create a 1 type row (land)
			else {
				Rows.push_back(new Row(columns, 1, t_width, t_height, i, rows, atlas));
			}

		}

	}

	//draw each tile in Tiles vector
	void drawGrid() {

		std::cout << "Player row: " << player->getRow() << std::endl;

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

		//scroll up
		if (scroll > 10) {

			scroll = 0;

			//select random row type
			int type = 0 + (int)(rand() / (double)(RAND_MAX + 1) * (10 - 0 + 1));

			//if last row created was water 
			// create a 2 row (mover)
			if (last == 0) {
				last = 2;
				Rows.push_back(new Row(columns, 2, t_width, t_height, rows, rows, atlas));
			}
			//create a 0 row (water)
			else if (type < 5) {
				last = 0;
				Rows.push_back(new Row(columns, 0, t_width, t_height, rows, rows, atlas));
			}
			//create a 1 type row (land)
			else {
				last = 1;
				Rows.push_back(new Row(columns, 1, t_width, t_height, rows, rows, atlas));
			}

			
			for (int i = 0; i < Rows.size(); i++) {
				Rows[i]->increaseRow();
			}
			player->increaseRow();
			std::cout << "Player update: " << player->getRow() << std::endl;
			
			delete Rows.front();
			Rows.erase(Rows.begin());
			/*if (addedRows > 2) {
				delete Rows.front();
				Rows.erase(Rows.begin());
				addedRows = 2;
			}*/


		}

		//update rows
		for (int i = 0; i < Rows.size(); i++) {

			Rows[i]->update(elaTime);

		}

		//check if player is on movable tile and move them
		if (checkCollision(player->getRow(), player->getCol() - 1) == false) {
			if (checkMovable(player->getRow(), player->getCol() - 1) == true && elaTime == 60) {
				player->moveLeft();
				std::cout << "player move left" << std::endl;
			}
		}

		//if player died reset grid
		if (this->dead) {
			for (int i = 0; i < Rows.size(); i++) {
				delete Rows[i];
			}
			Rows.clear();

			initGrid();

			this->dead = false;
			delete this->player;
			this->player = new Player(0, 0, t_width, t_height, 0, floor(columns / 2), rows, atlas);

			elaTime = 0;
			addedRows = 0;
			scroll = 0;
		}

		//reset
		if (elaTime > 60) {
			elaTime = 0;
			scroll++;
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
			this->dead = true;
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
			if (checkCollision(player->getRow() + 1, player->getCol()) == false) {
				player->moveUp();
				std::cout << "player move up" << std::endl;
			}
			else {
				std::cout << "player colision" << std::endl;
			}
			
			//check if dead
			if (checkDeath(player->getRow(), player->getCol()) == true) {
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
			}
			
			break;
		case 2:
			//move player down
			if (checkCollision(player->getRow()-1, player->getCol()) == false) {
				player->moveDown();
				std::cout << "player move down" << std::endl;
			}
			else {
				std::cout << "player colision" << std::endl;
			}

			//check if dead
			if (checkDeath(player->getRow(), player->getCol()) == true) {
				std::cout << "DEAD" << std::endl;
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
			}

			break;
		default:
			break;
		}
		
	}

};

