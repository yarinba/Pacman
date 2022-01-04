#pragma once

#include "Creature.h"
#include "Map.h"

class Fruit : public Creature {
	int numOfMoves = 0;
	bool isAlive = false;
public:
	Fruit();
	void create(char val, int x, int y);
	int getFruitVal();
	int getNumOfMoves() { return numOfMoves; }
	bool getIsAlive();
	void setIsAlive(bool _isAlive, bool isBreadcrumbPos = false);
	void move(const Map& map, int iterationNumber);
};