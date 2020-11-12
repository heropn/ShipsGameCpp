#include <iostream>
#include <random>
#include <Windows.h>
#include "GameManager.h"

GameManager::GameManager()
{
	std::cout << "How big should be the board (even number reccomended and has to be between 4 and 8): ";
	int boardSize = 0;

	std::cin >> boardSize;

	while (boardSize < 4 || boardSize > 8)
	{
		if (boardSize < 4 || boardSize > 8)
			std::cout << "Wrong value\n";

		std::cin >> boardSize;
	}

	this->boardSize = boardSize;

	std::cout << "How many players (1 or 2): ";
	int numberOfPlayers = 0;
	
	while (numberOfPlayers != 1 && numberOfPlayers != 2)
	{
		std::cin >> numberOfPlayers;

		if (numberOfPlayers != 1 && numberOfPlayers != 2)
			std::cout << "Wrong value\n";
	}

	this->numberOfPlayers = numberOfPlayers;

	if (numberOfPlayers == 1)
	{
		std::cout << "Do you wish to play 2-player game vs computer?" << std::endl << "Yes: type 1	No: type 0" << std::endl;
		int number = -1;
		versusComputer = false;

		while (number != 0 && number != 1)
		{
			std::cin >> number;

			if (number != 0 && number != 1)
				std::cout << "Wrong value\n";
		}
		
		if (number == 1)
			versusComputer = true;
	}
	
	system("CLS");

	isGameRunning = true;

	if (numberOfPlayers == 1)
	{
		if (versusComputer)
		{
			firstBoard = Board(boardSize);
			SetShips(firstBoard, firstPlayerShips);
			secondBoard = Board(boardSize);
			SetShips(secondBoard, secondPlayersShips);
		}
		else
		{
			firstBoard = Board(boardSize);
			SetShips(firstBoard, firstPlayerShips);
		}
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
		if (versusComputer)
		{
			bool firstPlayerWon = true;

			while (isGameRunning)
			{
				system("CLS");

				std::cout << "You:\n";

				firstBoard.SpawnBoard();

				Move(firstBoard, firstPlayerShips, "You");

				if (!isGameRunning)
				{
					firstPlayerWon = true;
					continue;
				}

				system("CLS");
				std::cout << "Computer moves in: ";
				for (int i = waitBetweenPlayersSeconds; i > 0; i--)
				{
					std::cout << i << std::endl;
					Wait(1);
				}

				system("CLS");

				std::cout << "Computer:\n";

				secondBoard.SpawnBoard();

				Move(secondBoard, secondPlayersShips, "Computer", true);

				if (!isGameRunning)
				{
					firstPlayerWon = false;
					continue;
				}

				system("CLS");
				std::cout << "Your move in: ";
				for (int i = waitBetweenPlayersSeconds; i > 0; i--)
				{
					std::cout << i << std::endl;
					Wait(1);
				}
			}

			if (firstPlayerWon)
				std::cout << "Congratulations you've won :D" << std::endl;
			else
				std::cout << "Unfortunately computer won :(" << std::endl;
		}
		else
		{
			while (isGameRunning)
			{
				bool areValuesProper = false;

				Move(firstBoard, firstPlayerShips, "You");

				system("CLS");
				std::cout << "You:\n";
				firstBoard.SpawnBoard();

				if (AreAllShipsDestroyed(firstPlayerShips))
				{
					isGameRunning = false;
				}
			}

			std::cout << "Congratulations you've won :D" << std::endl;
		}
	}
	else
	{
		bool firstPlayerWon = true;
		
		while (isGameRunning)
		{
			system("CLS");

			std::cout << "First Player:\n";
			
			firstBoard.SpawnBoard();

			Move(firstBoard, firstPlayerShips, "First Player");

			if (!isGameRunning)
				continue;

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

			Move(secondBoard, secondPlayersShips, "Second Player");

			if (!isGameRunning)
				continue;

			system("CLS");
			std::cout << "Next player in: ";
			for (int i = waitBetweenPlayersSeconds; i > 0; i--)
			{
				std::cout << i << std::endl;
				Wait(1);
			}
		}

		if (firstPlayerWon)
			std::cout << "Congratulations first player won :D" << std::endl;
		else
			std::cout << "Congratulations second player won :D" << std::endl;
	}

}

void GameManager::Move(Board& board, std::vector<Ship>& ships, std::string playerName, bool isComputer)
{
	int x, y;
	bool areValuesProper = false;
	Brick shootedBrick;

	if (!isComputer)
	{
		do
		{
			do
			{
				areValuesProper = false;

				std::cout << "Enter X value: ";
				std::cin >> x;
				std::cout << "Enter Y value: ";
				std::cin >> y;

				if (ShootBrick(board, x, y, shootedBrick))
				{
					areValuesProper = true;
					continue;
				}

				std::cout << "Wrong values, please try again" << std::endl;

			} while (!areValuesProper);

			system("CLS");
			std::cout << playerName << ":\n";
			board.SpawnBoard();

			if (AreAllShipsDestroyed(ships))
			{
				isGameRunning = false;
				continue;
			}

			Wait(waitShowTimeSeconds);

		} while (shootedBrick.isPartOfAShip && isGameRunning);
	}
	else
	{
		do
		{
			do
			{

				areValuesProper = false;

				std::random_device device;
				std::mt19937 generator(device());
				std::uniform_int_distribution<int> distribution(1, this->boardSize);

				x = distribution(generator);
				y = distribution(generator);

				if (ShootBrick(secondBoard, x, y, shootedBrick))
				{
					areValuesProper = true;
					continue;
				}

			} while (!areValuesProper);

			system("CLS");
			std::cout << playerName << ":\n";
			board.SpawnBoard();

			if (AreAllShipsDestroyed(ships))
			{
				isGameRunning = false;
				continue;
			}

			Wait(waitShowTimeSeconds);

		} while (shootedBrick.isPartOfAShip && isGameRunning);
	}
}

bool GameManager::ShootBrick(Board& board, int xBrick, int yBrick, Brick& emptyBrickPtr)
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
			emptyBrickPtr = board.bricks[i];
			return true;
		}
	}
	return true;
}

void GameManager::SetShips(Board& board, std::vector<Ship>& playerShipsVector)
{
	int biggestShipSize = this->boardSize / 2;
	int shipSize = biggestShipSize;

	for (int i = biggestShipSize; i > 0; i--)
	{
		int shipsNumber = this->boardSize / shipSize;
		if (shipSize != 1)
		{
			for (int j = shipsNumber; j > 0; j--)
			{
				SetShip(board, playerShipsVector, shipSize);
			}
		}
		else
		{
			for (int j = (shipsNumber / 2) - 1; j > 0; j--)
			{
				SetShip(board, playerShipsVector, shipSize);
			}
		}
		shipSize--;
	}

	// TEST HACK
	for (int i = 1; i < board.bricks.size(); i++) 
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

		int random = distribution(generator);

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

void GameManager::Wait(float seconds)
{
	Sleep(seconds * 1000.0f);
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

		if (playerShips[i].size == 0 && bricksDestroyed != 0)
		{
			std::cout << "You've destoyed a ship with size: " << playerShips[i].shipsBricks.size() << std::endl;
			//Wait(0.5f);
		}

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
