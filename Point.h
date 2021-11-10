#pragma once

#include "utils.h"
#include "enums.h"

class Point {
private:
	int x, y;
public:
	Point(int _x, int _y);
	int getX();
	int getY();
	void set(int _x, int _y);
	void move(Direction dir);
	void draw(char ch, Color color = Color::WHITE);
	~Point() {}
};