#include "Ship.h"

Ship::Ship(std::vector<Brick*>& bricksForShip, size_t size)
{
	this->size = size;
	shipsBricks = bricksForShip;

	for (size_t i = 0; i < size; i++)
	{
		shipsBricks[i]->SetPartOfAShip();
	}
}
