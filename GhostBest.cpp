#include "GhostBest.h"

/*
* TODO: write documentation
*/
void GhostBest::move(const Map& map, const Point& pacmanPos, int iterationNumber) {
	if (!(iterationNumber % 2)) {
		Direction dir = Movement::calculateNextMoveBFS(map, pos, pacmanPos);
		setDirection(dir);
		bool isBreadcrumbPos = (map.getPoint(pos) == '*');
		if (isBreadcrumbPos) pos.draw('*');
		else pos.draw(' ');
		pos.move(direction);
		pos.draw(symbol, color);
	}
}
