#pragma once

#include "Ghost.h"

class GhostNovice : public Ghost {

public:
	void move(const Map& map, const Point& pacmanPos, int iterationNumber) override;
};
