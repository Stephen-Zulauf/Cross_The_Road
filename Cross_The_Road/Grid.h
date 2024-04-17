#pragma once

#include "config.h"
#include "Land.h"
#include "Water.h"
#include "Player.h"
#include "Bridge.h"

class Grid {
private:

	//rows and columns in grid.
	int rows = 0;
	int columns = 0;

	//vector to contain all the tiles
	std::vector<std::vector<Tile*>> Tiles;

	//handle to window to draw grid on
	sf::RenderWindow* window = nullptr;

public:
	Grid(int nRows, int nColumns, float w_width, float w_height, sf::RenderWindow* nWindow) {

		//set window
		window = nWindow;

		//set rows and columns
		rows = nRows;
		columns = nColumns;

		//determine width/height of tiles from screen width/height of window
		//x
		float t_width = w_width / columns;
		//y
		float t_height = w_height / rows;

		//intialize grid with starting tiles
		for (int i = 0; i < rows; i++) {
			
			if (i > 0 && i != rows - 1) {
				//select random row type
				int type = 0 + (int)(rand() / (double)(RAND_MAX + 1) * (5 - 0 + 1));

				//create a water row
				if (type < 3) {
					Tiles.push_back(genWaterRow(t_width, t_height, i));
				}
				//create a land row
				else {
					Tiles.push_back(genLandRow(t_width, t_height, i));
				}

			}
			else {
				Tiles.push_back(genLandRow(t_width, t_height, i));
			}
			
		}
	}
	~Grid() {
		for (int i = 0; i < Tiles.size(); i++)
		{
			for (int j = 0; j < Tiles[i].size(); j++)
			{
				delete Tiles[i][j];
			}

		}
	}

	//generate randomized land row
	std::vector<Tile*> genLandRow(float t_width, float t_height, int i) {

		std::vector<Tile*> tempTiles;

		for (int j = 0; j < columns; j++) {
			Tile* temp = new Land(t_width * j, t_height * i, t_width, t_height);

			tempTiles.push_back(temp);
		}

		return tempTiles;
	}

	//generate randomized water row
	std::vector<Tile*> genWaterRow(float t_width, float t_height, int i) {

		std::vector<Tile*> tempTiles;

		int bridge = 0 + (int)(rand() / (double)(RAND_MAX + 1) * (columns - 0 + 1));

		for (int j = 0; j < columns; j++) {
			if (j == bridge) {
				Tile* temp = new Bridge(t_width * j, t_height * i, t_width, t_height);
				tempTiles.push_back(temp);
			}
			else {
				Tile* temp = new Water(t_width * j, t_height * i, t_width, t_height);
				tempTiles.push_back(temp);
			}

		}

		return tempTiles;
	}

	void drawGrid() {
		//draw each tile in Tiles vector

		for (int i = 0; i < Tiles.size(); i++) {
			for (int j = 0; j < Tiles[i].size(); j++) {
				Tiles[i][j]->draw(window);
			}
		}
	}

};