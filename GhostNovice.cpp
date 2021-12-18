#include "GhostNovice.h"

/*
* Get: The map by reference and iteration number of game loop
* (*) Execute only every second loop beacuse the pace of Ghost is half the pace of the Pacman
* (*) Move the Ghost position by 3 steps:
*		1a. if the ghost steped on a breadcrumb - print breadcrumb at current position
*		1b. else - print blank space at current position
*		2. change logical position
*		3. print the Ghost symbol at new logical position
*/
void GhostNovice::move(const Map& map, const Point& pacmanPos, int iterationNumber) {
	if (!(iterationNumber % 2)) {
		bool isBreadcrumbPos = Movement::noviceMove(*this, map, iterationNumber);
		if (isBreadcrumbPos) pos.draw('*');
		else pos.draw(' ');
		pos.move(direction);
		pos.draw(symbol, color);
	}
}
