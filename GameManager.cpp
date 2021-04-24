#include <iostream>
#include <random>
#include <sstream>
#include <Windows.h>
#include "GameManager.h"

void GameManager::Play()
{
	std::cout << "Jak wielka ma byc plansza (rozmiar musi zawierac sie pomiedzy 4 i 8): ";
	std::string boardSize = "0";

	std::cin >> boardSize;

	while (boardSize < "4" || boardSize > "8")
	{
		if (boardSize < "4" || boardSize > "8")
			std::cout << "Zla wartosc\n";

		std::cin >> boardSize;
	}

	//Zamienienie stringa na inta
	std::stringstream(boardSize) >> this->boardSize;

	std::cout << "Ile graczy (1 lub 2): ";
	std::string numberOfPlayersStr = "0";

	while (numberOfPlayersStr != "1" && numberOfPlayersStr != "2")
	{
		std::cin >> numberOfPlayersStr;

		if (numberOfPlayersStr != "1" && numberOfPlayersStr != "2")
			std::cout << "Zla wartosc\n";
	}
	
	//Zamienienie stringa na inta
	std::stringstream(numberOfPlayersStr) >> this->numberOfPlayers;

	if (this->numberOfPlayers == 1)
	{
		versusComputer = true;
	}

	std::cout << "Czy chcialbys ustawiac statki samodzielnie, czy chcesz zeby bylo to zrobione automatycznie?" << std::endl;

	std::string numberStr = "-";
	std::cout << "Automatyczne: napisz 1	Samodzielnie: napisz 0" << std::endl;

	while (numberStr != "0" && numberStr != "1")
	{
		std::cin >> numberStr;

		if (numberStr != "0" && numberStr != "1")
			std::cout << "Zla wartosc\n";
	}

	int number;

	//Zamienienie stringa na inta
	std::stringstream(numberStr) >> number;
	bool isAutomatic = number;

	system("CLS");

	isGameRunning = true;

	//Przygotowanie plansz do gry, odpowiednio od trybu oraz rozmieszczenie statkow
	if (this->numberOfPlayers == 1)
	{
		if (versusComputer)
		{
			firstBoard = Board(this->boardSize);
			secondBoard = Board(this->boardSize);
			SetShips(firstBoard, firstPlayerShips, "Ty", isAutomatic);
			SetShips(secondBoard, secondPlayersShips, "", true);
		}
		else
		{
			firstBoard = Board(this->boardSize);
			SetShips(firstBoard, firstPlayerShips, "Ty", isAutomatic);
		}
	}
	else
	{
		firstBoard = Board(this->boardSize);
		secondBoard = Board(this->boardSize);
		SetShips(firstBoard, firstPlayerShips, "Pierwszy Gracz", isAutomatic);

		if (!isAutomatic)
		{
			system("CLS");
			std::cout << "Nastpeny gracz za: ";
			for (int i = waitBetweenPlayersSeconds; i > 0; i--)
			{
				std::cout << i << std::endl;
				Wait(1);
			}
		}

		SetShips(secondBoard, secondPlayersShips, "Drugi Gracz", isAutomatic);
	}

	//Zaczecie gry
	if (numberOfPlayers == 1)
	{
		if (versusComputer)
		{
			bool firstPlayerWon = true;

			while (isGameRunning)
			{
				system("CLS");

				std::cout << "Ty:\n";

				secondBoard.SpawnBoard();

				Move(secondBoard, secondPlayersShips, "Ty");

				if (!isGameRunning)
				{
					firstPlayerWon = true;
					continue;
				}

				system("CLS");
				std::cout << "Tura komputera za: ";
				for (int i = waitBetweenPlayersSeconds; i > 0; i--)
				{
					std::cout << i << std::endl;
					Wait(1);
				}

				system("CLS");

				std::cout << "Komputer:\n";

				firstBoard.SpawnBoard();
				Wait(1);

				MoveComputer(firstBoard, firstPlayerShips, "Komputer");

				if (!isGameRunning)
				{
					firstPlayerWon = false;
					continue;
				}

				system("CLS");
				std::cout << "Twoj ruch za: ";
				for (int i = waitBetweenPlayersSeconds; i > 0; i--)
				{
					std::cout << i << std::endl;
					Wait(1);
				}
			}

			if (firstPlayerWon)
				std::cout << "Gratulacje, wygrales! :)" << std::endl;
			else
				std::cout << "Niestety komputer wygral :(" << std::endl;
		}
		else
		{
			while (isGameRunning)
			{
				bool areValuesProper = false;

				system("CLS");
				std::cout << "Ty:\n";

				firstBoard.SpawnBoard();

				Move(firstBoard, firstPlayerShips, "Ty");

				system("CLS");
				std::cout << "Ty:\n";
				firstBoard.SpawnBoard();

				if (AreAllShipsDestroyed(firstPlayerShips))
				{
					isGameRunning = false;
				}
			}

			std::cout << "Gratulacje, wygrales! :)" << std::endl;
		}
	}
	else
	{
		bool firstPlayerWon = true;
		
		while (isGameRunning)
		{
			system("CLS");

			std::cout << "Pierwszy Gracz:\n";
			
			secondBoard.SpawnBoard();

			Move(secondBoard, secondPlayersShips, "Pierwszy Gracz");

			if (!isGameRunning)
				continue;

			system("CLS");
			std::cout << "Nastepny gracz za: ";
			for (int i = waitBetweenPlayersSeconds; i > 0; i--)
			{
				std::cout << i << std::endl;
				Wait(1);
			}

			system("CLS");

			std::cout << "Drugi gracz:\n";

			firstBoard.SpawnBoard();

			Move(firstBoard, firstPlayerShips, "Drugi gracz");

			if (!isGameRunning)
				continue;

			system("CLS");
			std::cout << "Nastpeny gracz za: ";
			for (int i = waitBetweenPlayersSeconds; i > 0; i--)
			{
				std::cout << i << std::endl;
				Wait(1);
			}
		}

		if (firstPlayerWon)
			std::cout << "Gratulacje, Pierwszy Gracz wygra³! :)" << std::endl;
		else
			std::cout << "Gratulacje, Drugi Gracz wygra³! :)" << std::endl;
	}

	Wait(3);
}

void GameManager::DisplayRules()
{
	std::cout << "Zasady gry:" << std::endl;
	std::cout << "\t1. Strzal w statki:" << std::endl;
	std::cout << "W statki strzelamy wpisujac odpowiednie wspolrzedne o ktore poprosi program, tj. A4, c5. Kolejnosc, ani wielkosc liter nie ma znaczenia" << std::endl;
	std::cout << "\t2. Wybieranie miejsc na ustawienie statkow:" << std::endl;
	std::cout << "Statki ustawiamy najpierw decydujac, czy chcemy dany statek ustawic horyzontalnie lub wertykalnie, a nastepnie" << std::endl;
	std::cout << "wybieramy pole od ktorego chcemy go ustawic. Statki horyzontalne ustawiaja sie na prawo od wybranego pola, natomiast" << std::endl;
	std::cout << "statki wertykalne ustawiaja sie od wybranego pola do dolu." << std::endl;
	std::cout << "\t3. Cel gry" << std::endl;
	std::cout << "Gra konczy sie w momencie, w ktorym ktorys z graczy zestrzeli wszystkie statki przeciwnika" << std::endl;

}

void GameManager::GetCoordinates(int& x, int& y)
{
	bool areValuesProper = true;

	//Petla ktora bedzie sie wykonowyala dopoki gracze nie wpisze poprawnych koordynatow na pole
	do
	{
		if (!areValuesProper)
			std::cout << "Zla wartosc" << std::endl;

		areValuesProper = false;
		std::string input;

		std::cout << "Wpisz koordynaty pola: ";
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
		//Petla ktora sprawdza czy dane koordynaty na pole sa poprawne
		do
		{
			if (!areValuesProper)
				std::cout << "Zle wartosci" << std::endl;

			areValuesProper = false;

			GetCoordinates(x, y);

			if (ShootBrick(board, x, y, shootedBrick))
			{
				areValuesProper = true;
			}	

		} while (!areValuesProper);

		//Pojawienia sie zakutalizowanej planszy z nowo zestrzelonym polem
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

			//Stworzenie generatora do pseudo losowych liczb i wygenerowanie losowych wspolrzednych
			std::random_device device;
			std::mt19937 generator(device());
			std::uniform_int_distribution<int> distribution(1, this->boardSize);

			x = distribution(generator);
			y = distribution(generator);

			Ship* ship = nullptr;

			//If, ktory wykona sie jezeli w poprzednim ruchu komputer trafi statek i nie zostal on zatopiony
			if (lastShootedComputerBrick != nullptr && 
				lastShootedComputerBrick->isPartOfAShip == true && 
				!IsShipDestroyed(firstPlayerShips, lastShootedComputerBrick, ship))
			{
				std::uniform_int_distribution<int> distribution(-1, 1);

				//W zaleznosci czy statek jest ustawiony horyzontalnie, czy wertykalnie, strzelanie w losowo wybranym kierunku

				if (ship->position == Ship::Position::Horizontal)
				{
					x = lastShootedX + distribution(generator);
					y = lastShootedY;

					int index = x + ((y - 1) * boardSize) - 1;

					while (board.bricks[index].isPartOfAShip && board.bricks[index].state == Brick::State::Shot)
					{
						x += distribution(generator);
						index = x + ((y - 1) * boardSize) - 1;
					}
				}
				else
				{
					x = lastShootedX;
					y = lastShootedY + distribution(generator);

					int index = x + ((y - 1) * boardSize) - 1;

					while (board.bricks[index].isPartOfAShip && board.bricks[index].state == Brick::State::Shot)
					{
						y += distribution(generator);
						index = x + ((y - 1) * boardSize) - 1;
					}
				}

				if (ShootBrick(board, x, y, shootedBrick))
				{
					areValuesProper = true;
					continue;
				}
			}
			else
			{
				int index = x + ((y - 1) * boardSize) - 1;

				// Strzelenie komputera wtedy i tylko wtedy, gdy pole nie jest obok pola z zestrzelona juz czescia statku
				if (!CheckIfBrickConnectToAnyShip(board, index, true) && ShootBrick(board, x, y, shootedBrick))
				{
					areValuesProper = true;
					continue;
				}
			}

		} while (!areValuesProper);
		
		if (shootedBrick->isPartOfAShip)
		{
			lastShootedX = x;
			lastShootedY = y;
			lastShootedComputerBrick = shootedBrick;
		}

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
	//Walidacja wspolrzednych
	if (xBrick > boardSize || yBrick > boardSize || xBrick < 1 || yBrick < 1)
		return false;

	//wylizenie indexu bricka w vectorze
	int index = xBrick + ((yBrick - 1) * boardSize) - 1;

	if (board.bricks[index].state == Brick::State::Shot)
	{
		return false;
	}

	board.bricks[index].Shoot();
	emptyBrickPtr = &board.bricks[index];
	return true;
}

void GameManager::SetShips(Board& board, std::vector<Ship>& playerShipsVector, const std::string& playerName, bool isAutomatic)
{
	//Pojawienie sie wszystkich pol odkrytych jesli gracz wybral samodzielne rozstawienie statkow
	if (!isAutomatic)
	{
		system("cls");
		board.ShowAllBricks();
		std::cout << playerName << ":\n";
		board.SpawnBoard();
	}

	int biggestShipSize = this->boardSize / 2;
	int shipSize = biggestShipSize;

	//Algorytm obliczajacy ile statkow ustawic w zaleznosci od rozmiaru planszy
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
		Wait(1);
	}
}

void GameManager::SetShipByPlayer(Board& board, std::vector<Ship>& playerShipsVector, int shipSize, const std::string& playerName)
{
	if (shipSize != 1)
	{
		std::cout << "Chcesz polozyc statek o rozmiarze " << shipSize << " wertykalnie, czy horyzotnalnie?" << std::endl;
		std::cout << "Wertykalnie: napisz 1	Horyzontalnie: napisz 0" << std::endl;
		int shipPlacment;
		std::string shipPlacementStr;
		
		do
		{
			std::cin >> shipPlacementStr;

			if (shipPlacementStr != "0" && shipPlacementStr != "1")
				std::cout << "Zla wartosc" << std::endl;

		} while (shipPlacementStr != "0" && shipPlacementStr != "1");

		std::stringstream(shipPlacementStr) >> shipPlacment;

		switch (shipPlacment)
		{
		case 0: // horyzontalnie
		{
			Brick* brick = nullptr;
			std::vector<Brick*> chosenBricks;
			std::vector<Brick*> bricksForShips;
			std::cout << "Horyzontalne statki sa polozone na prawo od wybranego pola" << std::endl;

			bool areValuesProper = true;
			int x, y;

			//Sprawdzenie, czy x i y sa poprawnie oraz czy jest tak statek i czy wszystkie pola wokol sa wolne
			do
			{
				if (!areValuesProper)
					std::cout << "Zla wartosc" << std::endl;

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

			Ship ship = Ship(bricksForShips, Ship::Position::Horizontal, shipSize);
			playerShipsVector.push_back(ship);
		}
		break;
		case 1: // vertykalnie
		{
			Brick* brick = nullptr;
			std::vector<Brick*> chosenBricks;
			std::vector<Brick*> bricksForShips;
			std::string xStr, yStr;
			std::cout << "Wertykalne statki sa polozone od wybranego pola do dolu" << std::endl;

			bool areValuesProper = true;
			int x, y;

			//Sprawdzenie, czy x i y sa poprawnie oraz czy jest tak statek i czy wszystkie pola wokol sa wolne
			do
			{
				if (!areValuesProper)
					std::cout << "Zla wartosc" << std::endl;

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

			Ship ship = Ship(bricksForShips, Ship::Position::Vertical, shipSize);
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

		std::cout << "Gdzie chcesz polozyc swoj statek o rozmiarze " << shipSize << '?' << std::endl;

		//Sprawdzenie, czy x i y sa poprawnie oraz czy jest tak statek i czy wszystkie pola wokol sa wolne
		do
		{
			if (!areValuesProper)
				std::cout << "Zla wartosc" << std::endl;

			areValuesProper = true;

			GetCoordinates(x, y);

			int index = x + ((y - 1) * boardSize) - 1;

			brick = &board.bricks[index];

			if (brick->isPartOfAShip || CheckIfBrickConnectToAnyShip(board, index))
				areValuesProper = false;

		} while (!areValuesProper);

		brick->SetPartOfAShip();
		bricksForShips.push_back(brick);

		Ship ship = Ship(bricksForShips, Ship::Position::Horizontal);
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
		case 0: // horyzontalnie
		{
			Brick* brick;
			std::vector<Brick*> chosenBricks;
			distribution = std::uniform_int_distribution<int>(0, (this->boardSize * this->boardSize) - 1);
			bool isEveryBrickAvaliable;

			do
			{
				chosenBricks.clear();

				random = distribution(generator);
				int rightSideDistance = this->boardSize - (random % this->boardSize); // Jak daleko z prawej strony

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

			Ship ship = Ship(bricksForShips, Ship::Position::Horizontal, shipSize);
			playerShipsVector.push_back(ship);
		}break;
		case 1: // wertykalnie
		{
			Brick* brick;
			std::vector<Brick*> chosenBricks;
			distribution = std::uniform_int_distribution<int>(0, ((this->boardSize * this->boardSize) - 1) - (this->boardSize * (shipSize - 1)));
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

			Ship ship = Ship(bricksForShips, Ship::Position::Vertical, shipSize);
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

		Ship ship = Ship(bricksForShips, Ship::Position::Horizontal);
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

	//Sprawdzenie czy wszystkie statki sa zniszczone
	for (size_t i = 0; i < playerShips.size(); i++)
	{
		int bricksDestroyed = 0;
		for (size_t j = 0; j < playerShips[i].shipsBricks.size() ; j++)
		{
			if (playerShips[i].shipsBricks[j]->state == Brick::State::Shot)
				bricksDestroyed++;
		}

		//Jezeli statek zostal zniszczony to wypisanie informacji o tym jaki mial rozmiar oraz ze zostal zniszczony
		if (playerShips[i].size == bricksDestroyed)
		{
			std::cout << "Zniszczony statek o rozmiarze: " << playerShips[i].shipsBricks.size() << std::endl;
			playerShips[i].size = 0;
		}

		sumOfSizes += playerShips[i].size;
	}
	if (sumOfSizes != 0)
		return false;
	else
		return true;
}

bool GameManager::IsShipDestroyed(std::vector<Ship>& playerShips, Brick* shipsBrick, Ship*& shipPtr)
{
	for (size_t i = 0; i < playerShips.size(); i++)
	{
		for (size_t j = 0; j < playerShips[i].size; j++)
		{
			if (playerShips[i].shipsBricks[j] == shipsBrick)
			{
				shipPtr = &playerShips[i];
				break;
			}
		}
	}

	if (shipPtr != nullptr)
	{
		for (size_t i = 0; i < shipPtr->size; i++)
		{
			if (shipPtr->shipsBricks[i]->state != Brick::State::Shot)
			{
				return false;
			}
		}
	}

	return true;
}

bool GameManager::CheckIfBrickConnectToAnyShip(Board& board, int brickIndex, bool computerMode)
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
		if (computerMode)
		{
			if (board.bricks[indexes[i]].isPartOfAShip && board.bricks[indexes[i]].state == Brick::State::Shot)
				return true;
		}
		else
		{
			if (board.bricks[indexes[i]].isPartOfAShip)
				return true;
		}
	}

	return false;
}
