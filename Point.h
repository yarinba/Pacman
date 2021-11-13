#pragma once

#include "utils.h"
#include "enums.h"

class Point {
private:
	int x = 0 , y = 0;
public:
	Point();
	Point(int _x, int _y);
	int getX() const;
	int getY() const;
	void set(int _x, int _y);
	void move(Direction dir);
	void draw(char ch, Color color = Color::WHITE) const;
	~Point() {}
};