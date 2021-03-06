#pragma once

#include "Map.h"
#include "Creature.h"

class Ghost: public Creature {

public:
	Ghost() :
		Creature(Point(0, 0), Direction(rand() % 4), Color::LIGHTMAGENTA, '$') {}
	virtual void move(const Map& map, const Point& pacmanPos ,int iterationNumber) = 0;
};