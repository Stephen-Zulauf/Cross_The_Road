#pragma once
#include "config.h"
#include "PlayerLogic.h"
#include "Menu.h"

class Timers {
private:

	//clock reference in main
	sf::Clock* clock;
	//grid reference to update
	Grid* grid;
	//logic refernce to update
	PlayerLogic* logic;
	//reference to main menu
	Menu* mainMenu;


	//target run speed
	float target = 1;

	//event timers
	float ellapsed = 0;
	float update = 0;
	float rowRemove = 0;
	float xOffset = 0;
	float yOffset = 0;
	float xOffsetIncrement = 0;
	float yOffsetIncrement = 0;

	//bools to see if event happens
	bool dead = false;
	bool updateEvent = false;
	bool rowRemoveEvent = false;
	bool rowAnimation = false;

	//score
	int score = 0;
	

public:
	
	Timers(sf::Clock* nClock, Grid* nGrid, PlayerLogic* nLogic, Menu* nMenu) {
		clock = nClock;
		grid = nGrid;
		logic = nLogic;
		mainMenu = nMenu;
	}

	void updateAll() {
		ellapsed = clock->getElapsedTime().asSeconds();
		//std::cout << ellapsed << std::endl;

		xOffsetIncrement =  (1/(grid->getTileSize().x))-.002;
		yOffsetIncrement =  ((1.0/7 / (grid->getTileSize().y)));
		xOffset += xOffsetIncrement;
		yOffset -= yOffsetIncrement;

		//update timers
		if (ellapsed >= target) {
			ellapsed = 0;
			update++;
			rowRemove++;
			score++;
			mainMenu->updateScore(score);
			clock->restart();
		}
		
		//set update event
		if (update >= 1) {
			updateEvent = true;
			update = 0;
			xOffset = 0;
			
		}

		//set row removal
		if (rowRemove >= 6) {
			yOffset = 0;
			rowRemoveEvent = true;
			rowRemove = 0;
			
		}

		//update logic, grid, menu
		grid->update(updateEvent, rowRemoveEvent, xOffset, yOffset);
		logic->loop(updateEvent, rowRemoveEvent, &dead, xOffset, yOffset);

		//reset timers
		updateEvent = false;
		rowRemoveEvent = false;

		//reset if player died
		if (dead == true) {
			score = 0;
			mainMenu->reset();
			reset();
			dead = false;
		}

	}

	//getters

	//get offset for drawing
	float getOffset() {
		return this->xOffset;
	}

	//setters

	//reset timers if player died
	void reset() {
		//event timers
		ellapsed = 0;
		update = 0;
		rowRemove = 0;
		xOffset = 0;
		yOffset = 0;

		//bools to see if event happens
		updateEvent = false;
		rowRemoveEvent = false;
	}




};