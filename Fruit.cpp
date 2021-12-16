#include "Fruit.h"

Fruit::Fruit() : Creature(Point(0,0), Direction::NONE, Color
::LIGHTCYAN, (((rand() % 5) + 5) + '0')) {};

/*
* Get: boolean that represents whether the Fruit stepped on breadcrumb or not
* Move the Fruit position by 3 steps:
*	1a. if true - print breadcrumb at current position
*	1b. if false - print blank space at current position
*	2. change logical position
*	3. print the Fruit symbol at new logical position
*/
void Fruit::move(bool posIsBreadcrumb) {
	if (posIsBreadcrumb) pos.draw('*');
	else pos.draw(' ');
	pos.move(direction);
	pos.draw(symbol, color);
}