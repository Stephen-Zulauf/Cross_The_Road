#pragma once

#include "config.h"
#include "Tile.h"

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

		//intialize grid with empty tiles
		for (int i = 0; i < rows; i++) {
			Tiles.push_back(std::vector<Tile*>());

			for (int j = 0; j < columns; j++) {
				Tile* temp = new Tile( t_width * j, t_height * i, t_width, t_height);

				Tiles[i].push_back(temp);
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

	void drawGrid() {
		//draw each tile in Tiles vector

		for (int i = 0; i < Tiles.size(); i++) {
			for (int j = 0; j < Tiles[i].size(); j++) {
				Tiles[i][j]->draw(window);
			}
		}
	}

};