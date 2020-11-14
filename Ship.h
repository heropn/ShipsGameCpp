#pragma once
#include <vector>
#include "Brick.h"

class Ship
{
public:
	std::vector<Brick*> shipsBricks;
	int size;

	Ship(std::vector<Brick*>& bricksForShip, int size = 1);
};
