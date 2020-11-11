#include <iostream>
#include <random>
#include <Windows.h>
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
		SetShips(firstBoard, firstPlayerShips);
	}
	else
	{
		firstBoard = Board(boardSize);
		SetShips(firstBoard, firstPlayerShips);
		secondBoard = Board(boardSize);
		SetShips(secondBoard, secondPlayersShips);
	}
}

void GameManager::Play()
{
	int x, y;
	if (numberOfPlayers == 1)
	{
		while (isGameRunning)
		{
			bool areValuesProper = false;

			do
			{
				areValuesProper = false;

				std::cout << "Enter X value: ";
				std::cin >> x;
				std::cout << "Enter Y value: ";
				std::cin >> y;

				if (ShootBrick(firstBoard, x, y))
				{
					areValuesProper = true;
					continue;
				}
					
				std::cout << "Wrong values, please try again" << std::endl;

			} while (!areValuesProper);

			system("CLS");
			firstBoard.SpawnBoard();

			if (AreAllShipsDestroyed(firstPlayerShips))
			{
				isGameRunning = false;
			}
		}

		std::cout << "Congratulations you've won :D" << std::endl;
	}
	else
	{
		while (isGameRunning)
		{
			system("CLS");

			std::cout << "First Player:\n";
			
			firstBoard.SpawnBoard();

			bool areValuesProper = false;

			do
			{
				areValuesProper = false;

				std::cout << "Enter X value: ";
				std::cin >> x;
				std::cout << "Enter Y value: ";
				std::cin >> y;

				if (ShootBrick(firstBoard, x, y))
				{
					areValuesProper = true;
					continue;
				}

				std::cout << "Wrong values, please try again" << std::endl;

			} while (!areValuesProper);

			system("CLS");
			std::cout << "First Player:\n";
			firstBoard.SpawnBoard();

			if (AreAllShipsDestroyed(firstPlayerShips))
			{
				isGameRunning = false;
				continue;
			}

			Wait(waitShowTimeSeconds);

			system("CLS");
			std::cout << "Next player in: ";
			for (int i = waitBetweenPlayersSeconds; i > 0; i--)
			{
				std::cout << i << std::endl;
				Wait(1);
			}

			system("CLS");

			std::cout << "Second Player:\n";
			
			secondBoard.SpawnBoard();

			do
			{
				areValuesProper = false;

				std::cout << "Enter X value: ";
				std::cin >> x;
				std::cout << "Enter Y value: ";
				std::cin >> y;

				if (ShootBrick(secondBoard, x, y))
				{
					areValuesProper = true;
					continue;
				}

				std::cout << "Wrong values, please try again" << std::endl;

			} while (!areValuesProper);

			system("CLS");
			std::cout << "Second Player:\n";
			secondBoard.SpawnBoard();

			if (AreAllShipsDestroyed(secondPlayersShips))
			{
				isGameRunning = false;
				continue;
			}

			Wait(waitShowTimeSeconds);

			system("CLS");
			std::cout << "Next player in: ";
			for (int i = waitBetweenPlayersSeconds; i > 0; i--)
			{
				std::cout << i << std::endl;
				Wait(1);
			}
		}

		std::cout << "Congratulations you've won :D" << std::endl;
	}

}

bool GameManager::ShootBrick(Board& board, int xBrick, int yBrick)
{
	if (xBrick > boardSize || yBrick > boardSize)
		return false;

	for (int i = 0; i < board.bricks.size(); i++)
	{
		if (xBrick == board.bricks[i].x && yBrick == board.bricks[i].y)
		{
			if (board.bricks[i].state == Brick::BrickState::Shot)
			{
				return false;
			}

			board.bricks[i].Shoot();
			return true;
		}
	}
}

void GameManager::SetShips(Board& board, std::vector<Ship>& playerShipsVector)
{
	//SetShip(board, 3);
	//SetShip(board, 3);
	SetShip(board, playerShipsVector, 2);
	//SetShip(board, 2);
	//SetShip(board, 1);
	SetShip(board, playerShipsVector, 1);

	for (int i = 0; i < board.bricks.size(); i++) // TEST HACK
	{
		//board.bricks[i].Shoot();
	}
}

void GameManager::SetShip(Board& board, std::vector<Ship>& playerShipsVector, int shipSize)
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
			playerShipsVector.push_back(ship);
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
			playerShipsVector.push_back(ship);
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
		playerShipsVector.push_back(ship);
	}
}

void GameManager::Wait(int seconds)
{
	Sleep(seconds * 1000);
}

bool GameManager::AreAllShipsDestroyed(std::vector<Ship>& playerShips)
{
	int sumOfSizes = 0;

	for (int i = 0; i < playerShips.size(); i++)
	{
		int bricksDestroyed = 0;
		for (int j = 0; j < playerShips[i].size; j++)
		{
			if (playerShips[i].shipsBricks[j]->state == Brick::BrickState::Shot)
				bricksDestroyed++;
		}

		playerShips[i].size -= bricksDestroyed;
		sumOfSizes += playerShips[i].size;
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