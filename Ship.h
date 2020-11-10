#pragma once
#include <vector>
#include "Brick.h"

class Ship
{
public:
	int size;
	std::vector<Brick*> shipsBricks;

	Ship(std::vector<Brick*> bricksForShip, int size = 1);
};
