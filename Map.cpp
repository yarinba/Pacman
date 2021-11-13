#include "Map.h"

void Map::draw() {
	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 62; j++) {
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

void Map::setPoint(Point coord, char newVal) {
	map[coord.getY()][coord.getX()] = newVal;
}

char Map::getPoint(Point coord) {
	return map[coord.getY()][coord.getX()];
}