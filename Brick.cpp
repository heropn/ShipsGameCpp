#include "Brick.h"

Brick::Brick()
{
	isPartOfAShip = false;
	state = BrickState::Hidden;
	x = 0;
	y = 0;
}

Brick::Brick(int x, int y)
{
	this->x = x;
	this->y = y;
	isPartOfAShip = false;
	state = BrickState::Hidden;
}

char Brick::Spawn()
{
	if (state == BrickState::Hidden)
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
	state = BrickState::Shot;
}

void Brick::Show()
{
	state = BrickState::Showed;
}

void Brick::Hide()
{
	state = BrickState::Hidden;
}