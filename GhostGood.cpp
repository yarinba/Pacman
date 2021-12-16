#include "GhostGood.h"

/*
* TODO: write documentation
*/
void GhostGood::move(const Map& map, const Point& pacmanPos, int iterationNumber) {
	if (!(iterationNumber % 40)) {
		setDirection();
	}
	// Beacause the ghost move only every second iteration
	// iterationNumber % 40 counts as every 20 moves (same with 10 - 5 moves)
	else if (!(iterationNumber % 2) && (iterationNumber % 40 > 10)) {
		Direction dir = Movement::calculateNextMoveBFS(map, pos, pacmanPos);
		setDirection(dir);
	}
	if (!(iterationNumber % 2)) {
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
