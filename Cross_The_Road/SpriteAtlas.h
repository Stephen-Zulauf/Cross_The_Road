#pragma once

#include "config.h"
#include "TileSet.h"

class Atlas {
private:
	std::vector<TileSet> tileSets;
public:
	Atlas() {
		//load tile sets
		//0
		TileSet water(64, 16, 1, 4, "Water.png");
		tileSets.push_back(water);
		//1
		TileSet land(176, 112, 7, 11, "Grass.png");
		tileSets.push_back(land);
		//2
		TileSet bridge(144, 80, 5, 9, "Bridge.png");
		tileSets.push_back(bridge);
		//3
		TileSet player(192, 192, 4, 4, "Character.png");
		tileSets.push_back(player);
	}

	TileSet* getTileSet(int id) {
		return &tileSets[id];
	}

};