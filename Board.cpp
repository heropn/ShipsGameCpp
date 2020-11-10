#include <iostream>
#include <random>
#include "Brick.h"
#include "Ship.h"
#include "Board.h"

Board::Board(int size)
{
	this->size = size;
	isGameRunning = true;

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

	SetShips();
}

void Board::ShootBrickAndSpawnBoard(int xBrick, int yBrick)
{
	if (xBrick > size || yBrick > size)
	{
		std::cout << "Wrong values, please try again" << std::endl;
		return;
	}

	system("CLS");

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
					reveledBricks.push_back(&bricks[index]);
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

void Board::SetShips()
{
	SetShip(3);
	SetShip(3);
	SetShip(2);
	SetShip(2);
	SetShip(1);
	SetShip(1);

	for (int i = 0; i < bricks.size(); i++) // TEST HACK
	{
		bricks[i].Shoot();
	}
}

void Board::SetShip(int shipSize)
{
	std::vector<Brick*> bricksForShips;
	std::random_device device;
	std::mt19937 generator(device());

	if (shipSize != 1)
	{
		std::uniform_int_distribution<int> distribution(0, (this->size * this->size) - 1);

		int random = 1;

		switch (random % 2)
		{
		case 0: // horizontal
		{
			Brick* brick;
			std::vector<Brick*> chosenBricks;
			distribution = std::uniform_int_distribution<int>(0, (this->size * this->size) - 1);
			bool isEveryBrickAvaliable;

			do
			{
				chosenBricks.clear();

				random = distribution(generator);
				int rightSideDistance = this->size - (random % this->size); // how far away from right side

				while (rightSideDistance < shipSize)
				{
					random = distribution(generator);
					rightSideDistance = this->size - (random % this->size);
				}

				brick = &bricks[random];
				chosenBricks.push_back(brick);

				int countBricks = shipSize - 1;
				isEveryBrickAvaliable = true;

				if (CheckIfBrickConnectToAnyShip(random))
				{
					isEveryBrickAvaliable = false;
					continue;
				}

				while (countBricks > 0)
				{
					int indexToRight = random + countBricks;
					if (bricks[indexToRight].isPartOfAShip || CheckIfBrickConnectToAnyShip(indexToRight))
					{
						isEveryBrickAvaliable = false;
						break;
					}

					chosenBricks.push_back(&bricks[indexToRight]);
					countBricks--;
				}

			} while (brick->isPartOfAShip || !isEveryBrickAvaliable);

			for (int i = 0; i < chosenBricks.size(); i++)
			{
				chosenBricks[i]->SetPartOfAShip();
				bricksForShips.push_back(chosenBricks[i]);
			}

			Ship ship = Ship(bricksForShips, shipSize);
			ships.push_back(ship);
		}break;
		case 1: // vertical
		{
			Brick* brick;
			std::vector<Brick*> chosenBricks;
			distribution = std::uniform_int_distribution<int>(0, ((this->size * this->size) - 1) - (this->size * (shipSize - 1))); //maxindex - (boardSize * (shipSize - 1))
			bool isEveryBrickAvaliable;

			do
			{
				chosenBricks.clear();

				random = distribution(generator);
				brick = &bricks[random];
				chosenBricks.push_back(brick);

				int countBricks = shipSize - 1;
				isEveryBrickAvaliable = true;

				if (CheckIfBrickConnectToAnyShip(random))
				{
					isEveryBrickAvaliable = false;
					continue;
				}

				while (countBricks > 0)
				{
					int indexBelow = random + ((this->size) * countBricks);
					if (bricks[indexBelow].isPartOfAShip || CheckIfBrickConnectToAnyShip(indexBelow))
					{
						isEveryBrickAvaliable = false;
						break;
					}

					chosenBricks.push_back(&bricks[indexBelow]);
					countBricks--;
				}

			} while (brick->isPartOfAShip || !isEveryBrickAvaliable);

			for (int i = 0; i < chosenBricks.size(); i++)
			{
				chosenBricks[i]->SetPartOfAShip();
				bricksForShips.push_back(chosenBricks[i]);
			}

			Ship ship = Ship(bricksForShips, shipSize);
			ships.push_back(ship);
		}break;
		}

	}
	else
	{

		std::uniform_int_distribution<int> distribution(0, (this->size * this->size) - 1);

		Brick* brick;
		int random;
		bool isBrickAvaliable;

		do
		{
			isBrickAvaliable = true;
			random = distribution(generator);
			brick = &bricks[random];

		} while (brick->isPartOfAShip || CheckIfBrickConnectToAnyShip(random));

		brick->SetPartOfAShip();
		bricksForShips.push_back(brick);

		Ship ship = Ship(bricksForShips);
		ships.push_back(ship);
	}
}

bool Board::CheckIfBrickConnectToAnyShip(int brickIndex)
{
	int indexBelow = (brickIndex + this->size > (this->size * this->size) - 1) ? brickIndex : brickIndex + this->size;
	int indexAbove = (brickIndex - this->size < 0) ? brickIndex : brickIndex - this->size;
	int indexToRight = ((brickIndex + 1) % this->size == 0) ? brickIndex : brickIndex + 1;
	int indexToLeft = ((brickIndex - 1) % this->size == this->size - 1) || ((brickIndex - 1) < 0) ? brickIndex : brickIndex - 1;

	int indexes[4] = { indexBelow, indexAbove, indexToRight, indexToLeft };

	for (int i = 0; i < 4; i++)
	{
		if (bricks[indexes[i]].isPartOfAShip)
			return true;
	}

	return false;
}