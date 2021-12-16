#pragma once

#include "Ghost.h"
#include "Movement.h"

class GhostBest : public Ghost {

public:
	void move(const Map& map, const Point& pacmanPos, int iterationNumber) override;
};
