#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "Map.h"
#include "Point.h"
#include "Enums.h"
#include "utils.h"

class Map {
	bool isColored = true;
	char map[MAP_BOUNDARIES::Y][MAP_BOUNDARIES::X + 1];
public:
	void init();
	void draw() const;
	void setIsColored(bool _isColored);
	void setPoint(const Point& coord, char newVal);
	char getPoint(const Point& coord) const;
};
