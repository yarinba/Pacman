#pragma once

#include "Point.h"
#include "Enums.h"

class Ghost {
	const char symbol = '$';
	Point pos;
	Direction direction = Direction::NONE;
	Color color = Color::LIGHTMAGENTA;

	// TODO: create functions
};