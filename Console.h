#pragma once

#include "Game.h"
#include "utils.h"

class Console {
	Game gameObj;
	void printScore() const;
	void printLives() const;
	void printMenu() const;
	void printLose() const;
	void printWon() const;
	void printInstructions() const;
	void printPause() const;
	void clearPause() const;
};