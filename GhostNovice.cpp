#include "GhostNovice.h"

/*
* Get: The map by reference and iteration number of game loop
* (*) Execute only every second loop beacuse the pace of Ghost is half the pace of the Pacman
* (*) Move the Ghost position by 3 steps:
*		1a. if the ghost steped on a breadcrumb - print breadcrumb at current position
*		1b. else - print blank space at current position
*		2. change logical position
*		3. print the Ghost symbol at new logical position
* (*) Will change direction if one of the following occurs:
*		1. Every 20 iterations
*		2. if the ghost hit a wall / invisible tunnel
*		3. currrent direction is NONE
*/
void GhostNovice::move(const Map& map, const Point& pacmanPos, int iterationNumber) {
	if (!(iterationNumber % 2)) {
		bool everyTwentyIterations = !(iterationNumber % 20);
		bool noDirection = direction == Direction::NONE ? true : false;

		if (everyTwentyIterations || noDirection)
			setDirection();

		bool isWall = map.isWall(pos, direction, false);
		bool isInBoundaries = map.isInBoundaries(pos.getY(), pos.getX());
		while (isWall || !isInBoundaries) {
			setDirection();
			isWall = map.isWall(pos, direction, false);
			isInBoundaries = map.isInBoundaries(pos.getY(), pos.getX());
		} 

		bool isBreadcrumbPos = (map.getPoint(pos) == '*');
		if (isBreadcrumbPos) pos.draw('*');
		else pos.draw(' ');
		pos.move(direction);
		pos.draw(symbol, color);
	}
}
