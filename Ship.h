#pragma once
#include <vector>
#include "Brick.h"

class Ship
{
public:

	enum class Position
	{
		Vertical,
		Horizontal,
	};

	Position position;

	std::vector<Brick*> shipsBricks;
	size_t size;
	Ship(std::vector<Brick*>& bricksForShip, Position position, size_t size = 1);
};
