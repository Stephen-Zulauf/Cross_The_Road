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

	//track if player is dead
	bool dead = false;

	//vector of rows
	std::vector<Row*> Rows;

	//add sprite atlas
	Atlas* atlas = nullptr;

	//keep track of scrolling
	int scroll = 0;

	//keep track of last row type created
	int last = 1;

	//y offset for drawing
	float yOffset = 0.0;

public:
	//constructor
	Grid(int nRows, int nColumns, float w_width, float w_height, sf::RenderWindow* nWindow, Atlas* nAtlas) 
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
		atlas = nAtlas;

		//create row buffer
		rows += 2;

		initGrid();

	}
	
	//destructor
	~Grid() {
		for (int i = 0; i < Rows.size(); i++) {
			delete Rows[i];
		}
		Rows.clear();
	}

	//get total rows and columns
	sf::Vector2i getSize() {
		sf::Vector2i temp;
		temp.x = columns;
		temp.y = rows;
		return temp;
	}

	//get tile size
	sf::Vector2f getTileSize() {
		sf::Vector2f temp;
		temp.x = t_width;
		temp.y = t_height;
		return temp;
	}

	//get current atlas
	Atlas* getAtlas() {
		return this->atlas;
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
				else if (last == 1) {
					last = 0;
					Rows.push_back(new Row(columns, 0, t_width, t_height, i, rows, atlas));
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

		for (int i = Rows.size()-1; i >= 0; i--) {

			Rows[i]->draw(window);
		}

	}

	//set death
	//player logic interface setter
	void isDead(bool isDead) {
		this->dead = isDead;
	}

	//update moving tiles etc.
	void update(bool isUpdate, bool removal, float xOffset, float yOffset) {

		this->yOffset = yOffset;

		//if player died reset grid
		if (this->dead) {
			for (int i = 0; i < Rows.size(); i++) {
				delete Rows[i];
			}
			Rows.clear();

			initGrid();

			this->dead = false;

			scroll = 0;
		}

		

		//remove row from main clock
		if (removal) {

			//select random row type
			int type = 0 + (int)(rand() / (double)(RAND_MAX + 1) * (10 - 0 + 1));

			//if last row created was water 
			// create a 2 row (mover)
			if (last == 0) {
				last = 2;
				Rows.push_back(new Row(columns, 2, t_width, t_height, Rows.size() + 1, Rows.size()+1, atlas));
			}
			//create a 0 row (water)
			else if (type < 5) {
				last = 0;
				Rows.push_back(new Row(columns, 0, t_width, t_height, Rows.size() + 1, Rows.size()+1, atlas));
			}
			//create a 1 type row (land)
			else {
				last = 1;
				Rows.push_back(new Row(columns, 1, t_width, t_height, Rows.size() + 1, Rows.size()+1, atlas));
			}
			

			//TODO
			for (int i = 0; i < Rows.size(); i++) {
				Rows[i]->decreaseRow();
				
			}

			delete Rows.front();
			Rows.erase(Rows.begin());

		}

		//update tile animations
		for (int i = 0; i < Rows.size(); i++) {
			Rows[i]->updateTiles(xOffset, yOffset);
		}

		//if update from main clock
		if (isUpdate) {

			//update rows
			for (int i = 0; i < Rows.size(); i++) {

				Rows[i]->update(xOffset,yOffset);

			}
		}

	}

	//check if tile is walkable
	bool checkWalkable(int row, int col) {
		if (row < rows && row >= 0) {
			if (col < columns && col >= 0) {
				return this->Rows[row]->checkWalkable(col);
			}
		}
		else {
			return false;
		}
		
	}

	//check if players dead after move
	//returns true if dead
	bool checkDeath(int row, int col) {
		if (row < rows && row >= 0) {
			if (col < columns && col >= 0) {
				return this->Rows[row]->checkDeath(col);
			}
		}
		else {
			return false;
		}
	}

	//check if players on a movable tile after move
	//returns true if movable
	bool checkMovable(int row, int col) {
		if (row < rows && row >= 0) {
			if (col < columns && col >= 0) {
				return this->Rows[row]->checkMovable(col);
			}
		}
		else {
			return false;
		}

	}

	

};

