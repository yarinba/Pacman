#pragma once

#include "Creature.h"

class Fruit : public Creature {
public:
	Fruit();
	void move(bool posIsBreadcrumb);
};