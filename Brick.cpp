#include "Brick.h"

Brick::Brick()
{
	//default constructor
}

Brick::Brick(int x, int y)
{
	this->x = x;
	this->y = y;
	isPartOfAShip = false;
	state = Hidden;
}

char Brick::Spawn()
{
	if (state == Hidden)
	{
		return char(0xFE);
	}
	else
	{
		if (isPartOfAShip)
			return 'x';
		else
			return 'o';
	}
	return 'E';
}

void Brick::SetPartOfAShip()
{
	isPartOfAShip = true;
}

void Brick::Shoot()
{
	state = Shot;
}

void Brick::Show()
{
	state = Showed;
}

void Brick::Hide()
{
	state = Hidden;
}