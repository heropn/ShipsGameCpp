#include <iostream>
#include <random>
#include "GameManager.h"

GameManager::GameManager(int boardSize)
{
	std::cout << "How many players (1 or 2): ";
	int numberOfPlayers = 0;
	
	while (numberOfPlayers != 1 && numberOfPlayers != 2)
	{
		std::cin >> numberOfPlayers;

		if (numberOfPlayers != 1 && numberOfPlayers != 2)
			std::cout << "Wrong value\n";
	}

	this->numberOfPlayers = numberOfPlayers;
	
	system("CLS");

	this->boardSize = boardSize;
	isGameRunning = true;

	if (numberOfPlayers == 1)
	{
		firstBoard = Board(boardSize);
		SetShips(firstBoard);
	}
	else
	{
		firstBoard = Board(boardSize);
		SetShips(firstBoard);
		secondBoard = Board(boardSize);
		SetShips(secondBoard);
	}
}

void GameManager::Play()
{
	int x, y;
	if (numberOfPlayers == 1)
	{
		while (isGameRunning)
		{
			std::cout << "Enter X value: ";
			std::cin >> x;
			std::cout << "Enter Y value: ";
			std::cin >> y;

			ShootBrickAndSpawnBoard(firstBoard, x, y);
		}

		std::cout << "Congratulations you've won :D" << std::endl;
	}
	else
	{
		while (isGameRunning)
		{
			std::cout << "First Player:\n";

			std::cout << "Enter X value: ";
			std::cin >> x;
			std::cout << "Enter Y value: ";
			std::cin >> y;

			ShootBrickAndSpawnBoard(firstBoard, x, y);

			std::cout << "Second Player:\n";

			std::cout << "Enter X value: ";
			std::cin >> x;
			std::cout << "Enter Y value: ";
			std::cin >> y;

			ShootBrickAndSpawnBoard(secondBoard, x, y);
		}
	}

}

void GameManager::ShootBrickAndSpawnBoard(Board& board, int xBrick, int yBrick)
{
	if (xBrick > boardSize || yBrick > boardSize)
	{
		std::cout << "Wrong values, please try again" << std::endl;
		return;
	}

	system("CLS");

	board.SpawnBoard(xBrick, yBrick);
	
	if (CheckIfShipGotDestoyed())
		isGameRunning = false;
}

void GameManager::SetShips(Board& board)
{
	SetShip(board, 3);
	SetShip(board, 3);
	SetShip(board, 2);
	SetShip(board, 2);
	SetShip(board, 1);
	SetShip(board, 1);

	for (int i = 0; i < board.bricks.size(); i++) // TEST HACK
	{
		board.bricks[i].Shoot();
	}
}

void GameManager::SetShip(Board& board, int shipSize)
{
	std::vector<Brick*> bricksForShips;
	std::random_device device;
	std::mt19937 generator(device());

	if (shipSize != 1)
	{
		std::uniform_int_distribution<int> distribution(0, (this->boardSize * this->boardSize) - 1);

		int random = 1;

		switch (random % 2)
		{
		case 0: // horizontal
		{
			Brick* brick;
			std::vector<Brick*> chosenBricks;
			distribution = std::uniform_int_distribution<int>(0, (this->boardSize * this->boardSize) - 1);
			bool isEveryBrickAvaliable;

			do
			{
				chosenBricks.clear();

				random = distribution(generator);
				int rightSideDistance = this->boardSize - (random % this->boardSize); // how far away from right side

				while (rightSideDistance < shipSize)
				{
					random = distribution(generator);
					rightSideDistance = this->boardSize - (random % this->boardSize);
				}

				brick = &board.bricks[random];
				chosenBricks.push_back(brick);

				int countBricks = shipSize - 1;
				isEveryBrickAvaliable = true;

				if (CheckIfBrickConnectToAnyShip(board, random))
				{
					isEveryBrickAvaliable = false;
					continue;
				}

				while (countBricks > 0)
				{
					int indexToRight = random + countBricks;
					if (board.bricks[indexToRight].isPartOfAShip || CheckIfBrickConnectToAnyShip(board, indexToRight))
					{
						isEveryBrickAvaliable = false;
						break;
					}

					chosenBricks.push_back(&board.bricks[indexToRight]);
					countBricks--;
				}

			} while (brick->isPartOfAShip || !isEveryBrickAvaliable);

			for (int i = 0; i < chosenBricks.size(); i++)
			{
				chosenBricks[i]->SetPartOfAShip();
				bricksForShips.push_back(chosenBricks[i]);
			}

			Ship ship = Ship(bricksForShips, shipSize);
			firstPlayerShips.push_back(ship);
		}break;
		case 1: // vertical
		{
			Brick* brick;
			std::vector<Brick*> chosenBricks;
			distribution = std::uniform_int_distribution<int>(0, ((this->boardSize * this->boardSize) - 1) - (this->boardSize * (shipSize - 1))); //maxindex - (boardSize * (shipSize - 1))
			bool isEveryBrickAvaliable;

			do
			{
				chosenBricks.clear();

				random = distribution(generator);
				brick = &board.bricks[random];
				chosenBricks.push_back(brick);

				int countBricks = shipSize - 1;
				isEveryBrickAvaliable = true;

				if (CheckIfBrickConnectToAnyShip(board, random))
				{
					isEveryBrickAvaliable = false;
					continue;
				}

				while (countBricks > 0)
				{
					int indexBelow = random + ((this->boardSize) * countBricks);
					if (board.bricks[indexBelow].isPartOfAShip || CheckIfBrickConnectToAnyShip(board, indexBelow))
					{
						isEveryBrickAvaliable = false;
						break;
					}

					chosenBricks.push_back(&board.bricks[indexBelow]);
					countBricks--;
				}

			} while (brick->isPartOfAShip || !isEveryBrickAvaliable);

			for (int i = 0; i < chosenBricks.size(); i++)
			{
				chosenBricks[i]->SetPartOfAShip();
				bricksForShips.push_back(chosenBricks[i]);
			}

			Ship ship = Ship(bricksForShips, shipSize);
			firstPlayerShips.push_back(ship);
		}break;
		}

	}
	else
	{

		std::uniform_int_distribution<int> distribution(0, (this->boardSize * this->boardSize) - 1);

		Brick* brick;
		int random;
		bool isBrickAvaliable;

		do
		{
			isBrickAvaliable = true;
			random = distribution(generator);
			brick = &board.bricks[random];

		} while (brick->isPartOfAShip || CheckIfBrickConnectToAnyShip(board, random));

		brick->SetPartOfAShip();
		bricksForShips.push_back(brick);

		Ship ship = Ship(bricksForShips);
		firstPlayerShips.push_back(ship);
	}
}

bool GameManager::CheckIfShipGotDestoyed()
{
	int sumOfSizes = 0;

	for (int i = 0; i < firstPlayerShips.size(); i++)
	{
		int bricksDestroyed = 0;
		for (int j = 0; j < firstPlayerShips[i].size; j++)
		{
			if (firstPlayerShips[i].shipsBricks[j]->state == Brick::BrickState::Shot)
				bricksDestroyed++;
		}

		firstPlayerShips[i].size -= bricksDestroyed;
		sumOfSizes += firstPlayerShips[i].size;
	}
	if (sumOfSizes != 0)
		return false;
	else
		return true;
}

bool GameManager::CheckIfBrickConnectToAnyShip(Board& board, int brickIndex)
{
	int indexBelow = (brickIndex + this->boardSize > (this->boardSize * this->boardSize) - 1) ? brickIndex : brickIndex + this->boardSize;
	int indexAbove = (brickIndex - this->boardSize < 0) ? brickIndex : brickIndex - this->boardSize;
	int indexToRight = ((brickIndex + 1) % this->boardSize == 0) ? brickIndex : brickIndex + 1;
	int indexToLeft = ((brickIndex - 1) % this->boardSize == this->boardSize - 1) || ((brickIndex - 1) < 0) ? brickIndex : brickIndex - 1;

	int indexes[4] = { indexBelow, indexAbove, indexToRight, indexToLeft };

	for (int i = 0; i < 4; i++)
	{
		if (board.bricks[indexes[i]].isPartOfAShip)
			return true;
	}

	return false;
}