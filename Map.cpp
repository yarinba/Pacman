#include "Map.h"

void Map::init() {
	char newMap[MAP_BOUNDARIES::Y][MAP_BOUNDARIES::X + 1] = {
		// initial position pacman: Point(34, 17)
		// initial position ghost0: Point(48, 3)
		// initial position ghost1: Point(50, 3)
		"#################### #############   ###################   ##",
		"# * * * * * * * * * * * * * * * * * * * * * * * * * * * * * #",
		"# * * * * * * * * * * * * * * * * * * * * * * * * * * * * * #",
		"################# * * ######### * * * * * * * * $ $ * * * * #",
		"  * # * * * * * * * * * * * * # * * * * * * * * * * * * * *  ",
		"# * # * * # * * * * * * * * * ######### * * * * * * * * * * #",
		"# * # * * # * ##### * * * * * ######### * * * * * * * * * * #",
		"# * ########### * * * * * * * * * * * * * * * * * * * * * * #",
		"# * * * * * * ### * ########### * * * * * * #################",
		"# * * * * * * ### * ########### * * * * * * #################",
		"# * * * * * * ### * ########### * * * * * * #################",
		"  * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  ",
		"# * ####### * * * ### * ####### * * ##### * * * ### * #######",
		"# * * * * * * * * * * * * * * * * * * * * * * * * * * * * * #",
		"  * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  ",
		"### ########### ### * ######### * * * * * * ########### * * #",
		"# * * * * * * * * * * * * * * * * * * * * * * * * * * # * * #",
		"# * * * * * * * * * * * * * * * * @ * * * * * * * * * # * * #",
		"### ########### ### * ######### * * * * * * * * * * * # * * #",
		"# * * * * * * * * * * * * * * * * * * * * * ########### * * #",
		"# * * * * * * * * * * * * * * * * * * * * * * * * * * * * * #",
		"#################### #############   ###################   ##",
	};

	for (int i = 0; i < MAP_BOUNDARIES::Y; i++) {
		strcpy(map[i], newMap[i]);
	}
}


/*This function drawing each symbol according to the color we set for it*/
void Map::draw() const {
	gotoxy(0, 0);
	for (int i = 0; i < MAP_BOUNDARIES::Y; i++) {
		for (int j = 0; j < MAP_BOUNDARIES::X + 1; j++) {
			switch (map[i][j])
			{
			case '#':
				if (isColored) setTextColor(Color::BLUE);
				break;
			case '*':
				if (isColored) setTextColor(Color::LIGHTGREY);
				break;
			case '@':
				if (isColored) setTextColor(Color::YELLOW);
				break;
			case '$':
				if (isColored) setTextColor(Color::LIGHTMAGENTA);
				break;
			default:
				break;
			}
			std::cout << map[i][j];
		}
		std::cout << std::endl;
	}
	if (isColored) setTextColor(Color::WHITE);
}

void Map::setIsColored(bool _isColored) {
	isColored = _isColored;
}

// Get: Point coordinate and new char - set the new char in same coordinate on the map
void Map::setPoint(const Point& coord, char newVal) {
	map[coord.getY()][coord.getX()] = newVal;
}

/*
* Get: Point coordinate
* Return: current symbol in same coordinate on the map
*/
char Map::getPoint(const Point& coord) const {
	return map[coord.getY()][coord.getX()];
}
