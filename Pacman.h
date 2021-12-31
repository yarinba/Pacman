#pragma once

#include <cctype>
#include "Creature.h"

class Pacman: public Creature {
	const char arrowKeys[5] = { 'w', 'x', 'a', 'd', 's'};
public:
	Pacman();
	using Creature::getDirection;
	Direction getDirection(char key) const;
	void move(int rowSize, int colSize);
};