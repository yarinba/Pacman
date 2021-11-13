#include "Point.h"

Point::Point(): Point(0, 0) {}

Point::Point(int _x, int _y) : x(_x), y(_y) {}

int Point::getX() const {
	return x;
}

int Point::getY() const {
	return y;
}

void Point::set(int _x, int _y) {
	x = _x;
	y = _y;
}

void Point::move(Direction dir) {
	switch (dir) {
	case Direction::UP:
		--y;
		if (y < 0) {
			y = 21;
		}
		break;
	case Direction::DOWN:
		++y;
		if (y > 21) {
			y = 0;
		}
		break;
	case Direction::LEFT:
		--x;
		if (x < 0) {
			x = 60;
		}
		break;
	case Direction::RIGHT:
		++x;
		if (x > 60) {
			x = 0;
		}
		break;
	}
}

void Point::draw(char ch, Color color) const {
	setTextColor(color);
	gotoxy(x, y);
	std::cout << ch;
}