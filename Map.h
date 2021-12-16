#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "Map.h"
#include "Point.h"
#include "Enums.h"
#include "utils.h"

#include "Movement.h"

class Map {
	bool isColored = true;
	char map[MAP_BOUNDARIES::Y][MAP_BOUNDARIES::X + 1];
	//TODO: delete before merge
	friend class Movement;
private:
	Point calculateNextPos(Point pos, Direction dir) const;

public:
	//TODO: delete before merge
	int breadcrumbs = 430;
	int numOfGhosts = 2;
	Point GhostsLocations[2] = { Point(48, 3), Point(50, 3) };
	Point pacmanLocation = Point(34, 17);
	Point informationLocation = Point(0, 23);
	int rowSize = MAP_BOUNDARIES::Y;
	int colSize = MAP_BOUNDARIES::X;

	void init();
	void draw() const;
	void setIsColored(bool _isColored);
	void setPoint(const Point& coord, char newVal);
	char getPoint(const Point& coord) const;
	bool isWall(Point pos, Direction dir, bool isPacman = true) const;
	bool isInBoundaries(int row, int col) const {
		return (row > 0) && (col > 0)
			&& (row < rowSize) && (col < colSize);
	}
};
