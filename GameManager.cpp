#include <iostream>
#include <random>
#include <sstream>
#include <Windows.h>
#include "GameManager.h"

GameManager::GameManager()
{
	std::cout << "How big should be the board (number has to be between 4 and 8): ";
	std::string boardSize = "0";

	std::cin >> boardSize;

	while (boardSize < "4" || boardSize > "8")
	{
		if (boardSize < "4" || boardSize > "8")
			std::cout << "Wrong value\n";

		std::cin >> boardSize;
	}

	std::stringstream(boardSize) >> this->boardSize;

	std::cout << "How many players (1 or 2): ";
	std::string numberOfPlayersStr = "0";
	
	while (numberOfPlayersStr != "1" && numberOfPlayersStr != "2")
	{
		std::cin >> numberOfPlayersStr;

		if (numberOfPlayersStr != "1" && numberOfPlayersStr != "2")
			std::cout << "Wrong value\n";
	}

	std::stringstream(numberOfPlayersStr) >> this->numberOfPlayers;

	if (this->numberOfPlayers == 1)
	{
		std::cout << "Do you wish to play vs computer?" << std::endl << "Yes: type 1	No: type 0" << std::endl;
		std::string numberStr = "-";
		versusComputer = false;

		while (numberStr != "0" && numberStr != "1")
		{
			std::cin >> numberStr;

			if (numberStr != "0" && numberStr != "1")
				std::cout << "Wrong input\n";
		}
		
		if (numberStr == "1")
			versusComputer = true;
	}

	std::cout << "Do you want to place your ships by yourself or you want to let it be random?" << std::endl;

	std::string numberStr = "-";
	std::cout << "Automatic: Type 1	Place by yourself: Type 0" << std::endl;

	while (numberStr != "0" && numberStr != "1")
	{
		std::cin >> numberStr;

		if (numberStr != "0" && numberStr != "1")
			std::cout << "Wrong value\n";
	}
	
	int number;
	std::stringstream(numberStr) >> number;
	bool isAutomatic = number;
	
	system("CLS");

	isGameRunning = true;

	if (this->numberOfPlayers == 1)
	{
		if (versusComputer)
		{
			firstBoard = Board(this->boardSize);
			secondBoard = Board(this->boardSize);
			SetShips(firstBoard, firstPlayerShips, "You", isAutomatic);
			SetShips(secondBoard, secondPlayersShips, "", true);
		}
		else
		{
			firstBoard = Board(this->boardSize);
			SetShips(firstBoard, firstPlayerShips, "You", isAutomatic);
		}
	}
	else
	{
		firstBoard = Board(this->boardSize);
		secondBoard = Board(this->boardSize);
		SetShips(firstBoard, firstPlayerShips, "First Player", isAutomatic);

		if (!isAutomatic)
		{
			system("CLS");
			std::cout << "Next player in: ";
			for (int i = int(waitBetweenPlayersSeconds); i > 0; i--)
			{
				std::cout << i << std::endl;
				Wait(1);
			}
		}

		SetShips(secondBoard, secondPlayersShips, "Second Player", isAutomatic);
	}
}

void GameManager::Play()
{
	if (numberOfPlayers == 1)
	{
		if (versusComputer)
		{
			bool firstPlayerWon = true;

			while (isGameRunning)
			{
				system("CLS");

				std::cout << "You:\n";

				secondBoard.SpawnBoard();

				Move(secondBoard, secondPlayersShips, "You");

				if (!isGameRunning)
				{
					firstPlayerWon = true;
					continue;
				}

				system("CLS");
				std::cout << "Computer moves in: ";
				for (int i = int(waitBetweenPlayersSeconds); i > 0; i--)
				{
					std::cout << i << std::endl;
					Wait(1);
				}

				system("CLS");

				std::cout << "Computer:\n";

				firstBoard.SpawnBoard();
				Wait(0.5f);

				MoveComputer(firstBoard, firstPlayerShips, "Computer");

				if (!isGameRunning)
				{
					firstPlayerWon = false;
					continue;
				}

				system("CLS");
				std::cout << "Your move in: ";
				for (int i = int(waitBetweenPlayersSeconds); i > 0; i--)
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

				system("CLS");
				std::cout << "You:\n";

				firstBoard.SpawnBoard();

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
			
			secondBoard.SpawnBoard();

			Move(secondBoard, secondPlayersShips, "First Player");

			if (!isGameRunning)
				continue;

			system("CLS");
			std::cout << "Next player in: ";
			for (int i = int(waitBetweenPlayersSeconds); i > 0; i--)
			{
				std::cout << i << std::endl;
				Wait(1);
			}

			system("CLS");

			std::cout << "Second Player:\n";

			firstBoard.SpawnBoard();

			Move(firstBoard, firstPlayerShips, "Second Player");

			if (!isGameRunning)
				continue;

			system("CLS");
			std::cout << "Next player in: ";
			for (int i = int(waitBetweenPlayersSeconds); i > 0; i--)
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

	Wait(3.0f);
}

void GameManager::GetCoordinates(int& x, int& y)
{
	bool areValuesProper = true;
	do
	{
		if (!areValuesProper)
			std::cout << "Wrong values, please try again" << std::endl;

		areValuesProper = false;
		std::string input;

		std::cout << "Enter brick coordinates: ";
		std::cin >> input;

		if (input.size() != 2)
			continue;

		if (isdigit(input[0]) && isalpha(input[1]))
		{
			y = input[0] - '0';
			int diffrence = 'A' - 'a';

			if (isupper(input[1]))
			{
				input[1] -= diffrence;
			}

			if (input[1] < 'a' || input[1] > 'a' + boardSize - 1 || y < 1 || y > boardSize)
			{
				continue;
			}

			x = input[1] + 1 - 'a';
		}
		else if ((isdigit(input[1]) && isalpha(input[0])))
		{
			y = input[1] - '0';
			int diffrence = 'A' - 'a';

			if (isupper(input[0]))
			{
				input[0] -= diffrence;
			}

			if (input[0] < 'a' || input[0] > 'a' + boardSize - 1 || y < 1 || y > boardSize)
			{
				continue;
			}

			x = input[0] + 1 - 'a';
		}
		else
		{
			continue;
		}

		areValuesProper = true;

	} while (!areValuesProper);
}

void GameManager::Move(Board& board, std::vector<Ship>& ships, const std::string& playerName)
{
	int x = 0, y = 0;
	bool areValuesProper = true;
	Brick* shootedBrick = nullptr;

	do
	{
		do
		{
			if (!areValuesProper)
				std::cout << "Wrong values, please try again" << std::endl;

			areValuesProper = false;

			GetCoordinates(x, y);

			if (ShootBrick(board, x, y, shootedBrick))
			{
				areValuesProper = true;
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

	} while (shootedBrick->isPartOfAShip && isGameRunning);
}

void GameManager::MoveComputer(Board& board, std::vector<Ship>& ships, const std::string& computerName)
{
	int x = 0, y = 0;
	bool areValuesProper = true;
	Brick* shootedBrick = nullptr;

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

			if (ShootBrick(board, x, y, shootedBrick))
			{
				areValuesProper = true;
				continue;
			}

		} while (!areValuesProper);

		system("CLS");
		std::cout << computerName << ":\n";
		board.SpawnBoard();

		if (AreAllShipsDestroyed(ships))
		{
			isGameRunning = false;
			continue;
		}

		Wait(waitShowTimeSeconds);

	} while (shootedBrick->isPartOfAShip && isGameRunning);
}

bool GameManager::ShootBrick(Board& board, int xBrick, int yBrick, Brick*& emptyBrickPtr)
{
	if (xBrick > boardSize || yBrick > boardSize || xBrick < 1 || yBrick < 1)
		return false;


	int index = xBrick + ((yBrick - 1) * boardSize) - 1;

	if (board.bricks[index].state == Brick::BrickState::Shot)
	{
		return false;
	}

	board.bricks[index].Shoot();
	emptyBrickPtr = &board.bricks[index];
	return true;
}

void GameManager::SetShips(Board& board, std::vector<Ship>& playerShipsVector, const std::string& playerName, bool isAutomatic)
{
	if (!isAutomatic)
	{
		system("cls");
		board.ShowAllBricks();
		std::cout << playerName << ":\n";
		board.SpawnBoard();
	}

	int biggestShipSize = this->boardSize / 2;
	int shipSize = biggestShipSize;

	for (int i = biggestShipSize; i > 0; i--)
	{
		int shipsNumber = this->boardSize / shipSize;
		if (shipSize != 1)
		{
			for (int j = shipsNumber; j > 0; j--)
			{
				if (isAutomatic)
					SetShipAutomaticlly(board, playerShipsVector, shipSize);
				else
					SetShipByPlayer(board, playerShipsVector, shipSize, playerName);
			}
		}
		else
		{
			for (int j = (shipsNumber / 2) - 1; j > 0; j--)
			{
				if (isAutomatic)
					SetShipAutomaticlly(board, playerShipsVector, shipSize);
				else
					SetShipByPlayer(board, playerShipsVector, shipSize, playerName);
			}
		}
		shipSize--;
	}

	if (!isAutomatic)
	{
		board.HideAllBricks();
		Wait(1.0f);
	}
}

void GameManager::SetShipByPlayer(Board& board, std::vector<Ship>& playerShipsVector, int shipSize, const std::string& playerName)
{
	if (shipSize != 1)
	{
		std::cout << "Do you want to place ship with size " << shipSize << " vertical or horizontal?" << std::endl;
		std::cout << "Vertical: Type 1	Horizontal: Type 0" << std::endl;
		int shipPlacment;
		std::string shipPlacementStr;
		
		do
		{
			std::cin >> shipPlacementStr;

			if (shipPlacementStr != "0" && shipPlacementStr != "1")
				std::cout << "Wrong Value" << std::endl;

		} while (shipPlacementStr != "0" && shipPlacementStr != "1");

		std::stringstream(shipPlacementStr) >> shipPlacment;

		switch (shipPlacment)
		{
		case 0: // horizontal
		{
			Brick* brick = nullptr;
			std::vector<Brick*> chosenBricks;
			std::vector<Brick*> bricksForShips;
			std::cout << "Horizontal ships are placed from chosen brick to the right" << std::endl;

			bool areValuesProper = true;
			int x, y;

			//check if x and y are good, check if there is a ship, check if all bricks around are available
			do
			{
				if (!areValuesProper)
					std::cout << "Wrong values, please try again" << std::endl;

				chosenBricks.clear();
				areValuesProper = true;

				GetCoordinates(x, y);

				if (x > boardSize - shipSize + 1)
				{
					areValuesProper = false;
					continue;
				}

				int index = x + ((y - 1) * boardSize) - 1;

				brick = &board.bricks[index];
				chosenBricks.push_back(brick);

				if (brick->isPartOfAShip || CheckIfBrickConnectToAnyShip(board, index))
				{
					areValuesProper = false;
					continue;
				}

				int countBricks = shipSize - 1;

				while (countBricks > 0)
				{
					int indexToRight = index + countBricks;
					if (board.bricks[indexToRight].isPartOfAShip || CheckIfBrickConnectToAnyShip(board, indexToRight))
					{
						areValuesProper = false;
						break;
					}

					chosenBricks.push_back(&board.bricks[indexToRight]);
					countBricks--;
				}
			} while (!areValuesProper);

			for (size_t i = 0; i < chosenBricks.size(); i++)
			{
				chosenBricks[i]->SetPartOfAShip();
				bricksForShips.push_back(chosenBricks[i]);
			}

			Ship ship = Ship(bricksForShips, shipSize);
			playerShipsVector.push_back(ship);
		}
		break;
		case 1: // vertical
		{
			Brick* brick = nullptr;
			std::vector<Brick*> chosenBricks;
			std::vector<Brick*> bricksForShips;
			std::string xStr, yStr;
			std::cout << "Vertical ships are placed from chosen brick to the bottom" << std::endl;

			bool areValuesProper = true;
			int x, y;

			//check if x and y are good, check if there is a ship, check if all bricks around are available
			do
			{
				if (!areValuesProper)
					std::cout << "Wrong values, please try again" << std::endl;

				chosenBricks.clear();
				areValuesProper = true;

				GetCoordinates(x, y);

				if (y > boardSize - shipSize + 1)
				{
					areValuesProper = false;
					continue;
				}

				int index = x + ((y - 1) * boardSize) - 1;

				brick = &board.bricks[index];
				chosenBricks.push_back(brick);

				if (brick->isPartOfAShip || CheckIfBrickConnectToAnyShip(board, index))
				{
					areValuesProper = false;
					continue;
				}

				int countBricks = shipSize - 1;

				while (countBricks > 0)
				{
					int indexBelow = index + ((this->boardSize) * countBricks);
					if (board.bricks[indexBelow].isPartOfAShip || CheckIfBrickConnectToAnyShip(board, indexBelow))
					{
						areValuesProper = false;
						break;
					}

					chosenBricks.push_back(&board.bricks[indexBelow]);
					countBricks--;
				}
			} while (!areValuesProper);

			for (size_t i = 0; i < chosenBricks.size(); i++)
			{
				chosenBricks[i]->SetPartOfAShip();
				bricksForShips.push_back(chosenBricks[i]);
			}

			Ship ship = Ship(bricksForShips, shipSize);
			playerShipsVector.push_back(ship);
		}
		break;
		}

	}
	else
	{
		Brick* brick = nullptr;
		std::vector<Brick*> bricksForShips;
		std::string xStr, yStr;
		bool areValuesProper = true;
		int x, y;

		std::cout << "Where do you want to place ship with size " << shipSize << '?' << std::endl;

		do
		{
			if (!areValuesProper)
				std::cout << "Wrong values, please try again" << std::endl;

			areValuesProper = true;

			GetCoordinates(x, y);

			int index = x + ((y - 1) * boardSize) - 1;

			brick = &board.bricks[index];

			if (brick->isPartOfAShip || CheckIfBrickConnectToAnyShip(board, index))
				areValuesProper = false;

		} while (!areValuesProper);

		brick->SetPartOfAShip();
		bricksForShips.push_back(brick);

		Ship ship = Ship(bricksForShips);
		playerShipsVector.push_back(ship);
	}

	system("cls");
	std::cout << playerName << ":\n";
	board.SpawnBoard();
}

void GameManager::SetShipAutomaticlly(Board& board, std::vector<Ship>& playerShipsVector, int shipSize)
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

			for (size_t i = 0; i < chosenBricks.size(); i++)
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

			for (size_t i = 0; i < chosenBricks.size(); i++)
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

	for (size_t i = 0; i < playerShips.size(); i++)
	{
		int bricksDestroyed = 0;
		for (size_t j = 0; j < playerShips[i].shipsBricks.size() ; j++)
		{
			if (playerShips[i].shipsBricks[j]->state == Brick::BrickState::Shot)
				bricksDestroyed++;
		}

		if (playerShips[i].size == bricksDestroyed)
		{
			std::cout << "You've destoyed a ship with size: " << playerShips[i].shipsBricks.size() << std::endl;
			playerShips[i].size = 0;
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
	int indexBelow = (brickIndex + this->boardSize > (this->boardSize * this->boardSize) - 1) 
		? brickIndex 
		: brickIndex + this->boardSize;
	int indexAbove = (brickIndex - this->boardSize < 0) 
		? brickIndex 
		: brickIndex - this->boardSize;
	int indexToRight = ((brickIndex + 1) % this->boardSize == 0) 
		? brickIndex 
		: brickIndex + 1;
	int indexToLeft = ((brickIndex - 1) % this->boardSize == this->boardSize - 1) || ((brickIndex - 1) < 0) 
		? brickIndex 
		: brickIndex - 1;

	int indexes[4] = { indexBelow, indexAbove, indexToRight, indexToLeft };

	for (int i = 0; i < 4; i++)
	{
		if (board.bricks[indexes[i]].isPartOfAShip)
			return true;
	}

	return false;
}
