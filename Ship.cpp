#include "Ship.h"

Ship::Ship(std::vector<Brick*> bricksForShip, int size)
{
	this->size = size;
	shipsBricks = bricksForShip;

	for (int i = 0; i < size; i++)
	{
		shipsBricks[i]->SetPartOfAShip();
	}
}
