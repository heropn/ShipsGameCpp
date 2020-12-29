#include "Ship.h"

Ship::Ship(std::vector<Brick*>& bricksForShip, Position position, size_t size)
{
	this->position = position;
	this->size = size;
	shipsBricks = bricksForShip;

	for (size_t i = 0; i < size; i++)
	{
		shipsBricks[i]->SetPartOfAShip();
	}
}
