#pragma once
#include <vector>
#include "Brick.h"

class Ship
{
public:
	std::vector<Brick*> shipsBricks;
	size_t size;
	Ship(std::vector<Brick*>& bricksForShip, size_t size = 1);
};
