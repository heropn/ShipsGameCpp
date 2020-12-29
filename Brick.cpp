#include "Brick.h"

Brick::Brick()
{
	isPartOfAShip = false;
	state = State::Hidden;
	x = 0;
	y = 0;
}

Brick::Brick(unsigned int x, unsigned int y)
{
	this->x = x;
	this->y = y;
	isPartOfAShip = false;
	state = State::Hidden;
}

char Brick::Spawn()
{
	if (state == State::Hidden)
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
	state = State::Shot;
}

void Brick::Show()
{
	state = State::Showed;
}

void Brick::Hide()
{
	state = State::Hidden;
}