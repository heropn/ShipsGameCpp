#include <iostream>
#include <vector>
#include "Brick.h"
#include "Board.h"

Board::Board()
{
	this->size = 0;
}

Board::Board(int size)
{
	this->size = size;

	std::cout << " ";
	for (int i = 0; i < size + 1; i++)
	{
		for (int j = 0; j < size + 1; j++)
		{
			if (i != 0)
			{
				Brick brick = Brick(j, i);
				bricks.push_back(brick);
			}
		}
	}
}

void Board::ShowAllBricks()
{
	for (size_t i = 0; i < bricks.size(); i++)
		bricks[i].Show();
}

void Board::HideAllBricks()
{
	for (size_t i = 0; i < bricks.size(); i++)
		bricks[i].Hide();
}

void Board::SpawnBoard()
{
	int index = 0;
	std::cout << " ";
	for (int i = 0; i < size + 1; i++)
	{
		for (int j = 0; j < size + 1; j++)
		{
			if (i == 0 && j < size)
				std::cout << " " << char('A' + j);
			else if (j == 0 && i != 0)
				std::cout << i << " ";
			else if (i != 0)
			{
				std::cout << bricks[index++].Spawn() << " ";
			}
		}
		std::cout << std::endl;
	}
}
