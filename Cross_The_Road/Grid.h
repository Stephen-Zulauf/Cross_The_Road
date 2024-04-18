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
	sf::Vector2f playerLocation;
	Player* player = nullptr;

	//vector of rows
	std::vector<Row*> Tiles;

	//add sprite atlas
	Atlas* atlas = nullptr;
	

public:
	Grid(int nRows, int nColumns, float w_width, float w_height, Player n, sf::RenderWindow* nWindow) 
	{
		player = &n;

		//set window
		window = nWindow;

		//set rows and columns
		rows = nRows;
		columns = nColumns;

		//determine width/height of tiles from screen width/height of window
		t_width = w_width / columns;
		t_height = w_height / rows;

		//set starting player location
		playerLocation.y = 0;
		playerLocation.x = columns/2;

		//load tile sets
		atlas = new Atlas;

		initGrid();

	}
	
	~Grid() {
		for (int i = 0; i < Tiles.size(); i++) {
			delete Tiles[i];
		}
		Tiles.clear();
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

				//create a 0 row (water)
				if (type < 5) {
					Tiles.push_back(new Row(columns, 0, t_width, t_height, i, false, atlas));
				}
				//create a 1 type row (land)
				else {
					Tiles.push_back(new Row(columns, 1, t_width, t_height, i, false, atlas));
				}

			}
			else {
				Tiles.push_back(new Row(columns, 1, t_width, t_height, i, false, atlas));
			}

		}

	}

	//draw each tile in Tiles vector
	void drawGrid() {

		for (int i = 0; i < Tiles.size(); i++) {

			Tiles[i]->draw(window);
		}
	}

	void setplayer(Player n)
	{
		this->player = &n;
	}
	void moveplayer(int nRows, int nColumns)
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			nRows++;
			this->player->setPosition(nColumns, nRows);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			nColumns--;
			this->player->setPosition(nColumns, nRows);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			nRows--;
			this->player->setPosition(nColumns, nRows);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			nColumns++;
			this->player->setPosition(nColumns, nRows);
		}
	}

};

