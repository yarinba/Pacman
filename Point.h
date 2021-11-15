#pragma once

#include "utils.h"
#include "enums.h"


class Point {
	int x = 0 , y = 0;
public:
	Point();
	Point(int _x, int _y);
	friend bool operator== (const Point& p1, const Point& p2);
	int getX() const;
	int getY() const;
	void set(int _x, int _y);
	void move(Direction dir);
	void draw(char ch, Color color = Color::WHITE) const;
	~Point() {}
};