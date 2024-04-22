#pragma once

#include "config.h"

class TileSet {
private:
	int width = 0;
	int height = 0;

	int rows = 0;
	int columns = 0;

	float t_width = 0;
	float t_height = 0;

	std::string fileName;

	sf::Texture texture;

public:
	//width,height,rows,cols,filename
	TileSet(int nWidth, int nHeight, int nRows, int nCols, std::string nFileName) {
		this->width = nWidth;
		this->height = nHeight;
		this->fileName = nFileName;
		this->rows = nRows;
		this->columns = nCols;

		t_width = width / columns;
		t_height = height / rows;

		if (!texture.loadFromFile(nFileName))
		{
			std::cout << "ERR: Tileset failed to load texture from file: '" << fileName << "'" << std::endl;
		}
	}

	sf::Texture* getTexture() {
		return &this->texture;
	}

	sf::IntRect getTile(int tRow, int tCol, float wOffset = 0, float hOffset = 0) {
		sf::IntRect temp;

		temp.left = t_width * tCol;
		temp.top = t_height * tRow;

		temp.width = t_width + wOffset;
		temp.height = t_height + hOffset;

		return temp;

	}

};