#pragma once

#include "Ghost.h"

class GhostGood : public Ghost {

public:
	void move(const Map& map, const Point& pacmanPos, int iterationNumber) override;
};
