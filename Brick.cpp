#include "Brick.h"


	Brick::Brick(int x, int y)
	{
		this->x = x;
		this->y = y;
		isPartOfAShip = false;
		state = Hidden;
	}

	char Brick::Spawn()
	{
		switch (state)
		{
		case Brick::Hidden:
		{
			return char(0xFE);
		}break;
		case Brick::Shot:
		{
			if (isPartOfAShip)
				return 'x';
			else
				return 'o';
		}break;
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