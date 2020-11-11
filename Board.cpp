#include <iostream>
#include <vector>
#include "Brick.h"
#include "Board.h"

Board::Board()
{
	//default constructor
}

Board::Board(int size)
{
	this->size = size;

	std::cout << " ";
	for (int i = 0; i < size + 1; i++)
	{
		for (int j = 0; j < size + 1; j++)
		{
			if (i == 0 && j < size)
				std::cout << " " << j + 1;
			else if (j == 0 && i != 0)
				std::cout << i << " ";
			else if (i != 0)
			{
				Brick brick = Brick(j, i);
				std::cout << brick.Spawn() << " ";
				bricks.push_back(brick);
			}
		}
		std::cout << std::endl;
	}
}

void Board::SpawnBoard(int xBrick, int yBrick)
{
	int index = 0;
	std::cout << " ";
	for (int i = 0; i < size + 1; i++)
	{
		for (int j = 0; j < size + 1; j++)
		{
			if (i == 0 && j < size)
				std::cout << " " << j + 1;
			else if (j == 0 && i != 0)
				std::cout << i << " ";
			else if (i != 0)
			{
				if (xBrick == bricks[index].x && yBrick == bricks[index].y && bricks[index].state != Brick::Shot)
				{
					bricks[index].Shoot();
					std::cout << bricks[index].Spawn() << " ";
				}
				else
				{
					std::cout << bricks[index].Spawn() << " ";
				}

				index++;
			}
		}
		std::cout << std::endl;
	}
}
