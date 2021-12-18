#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "Point.h"
#include "Enums.h"
#include "Movement.h"
#include <string>
#include <fstream>

class Map {
	bool isColored = true;
	char map[MAP_BOUNDARIES::Y][MAP_BOUNDARIES::X + 1];
	int rowSize = 0;
	int colSize = 0;
	int numOfGhosts=0;
	int numOfBreadCrumbs=0;
	Point pacmanPos;
	Point GhostPos[4];
	Point mapStartingPoint;
	Point dataPos;
	friend class Movement;
  
private:
	void handleLegend(std::fstream& myfile, std::string &line, int& mapCol, int& currChar);
	void handleChar(char value, int& currCol);
	void getBoard(const char* fileName);
	Point calculateNextPos(Point pos, Direction dir) const;

public:
	void init(const char* fileName);
	void draw() const;
	void setIsColored(bool _isColored);
	void setPoint(const Point& coord, char newVal);
	char getPoint(const Point& coord) const;
	bool isWall(Point pos, Direction dir, bool isPacman = true) const;
	int getColSize() const { return colSize; }
	int getRowSize() const { return rowSize; }
	bool isInBoundaries(int row, int col) const {
		return (row > 0) && (col > 0)
			&& (row < rowSize) && (col < colSize);
	}
	int getNumOfGhosts() const { return numOfGhosts; }
	int getNumOfBreadCrumbs() const { return numOfBreadCrumbs; }
	const Point& getPacmanPos() const { return pacmanPos; }
	const Point& getDataPos() const { return dataPos;  }
	const Point* getGhostsPos() const { return GhostPos; }
};
