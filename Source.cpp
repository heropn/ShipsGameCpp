#include <iostream>
#include <vector>
#include <random>

class Brick
{
public:
	int x, y;
	bool isPartOfAShip;

	enum BrickState
	{
		Hidden,
		Shot,
	};

	BrickState state;

	Brick(int x, int y)
	{
		this->x = x;
		this->y = y;
		isPartOfAShip = false;
		state = Hidden;
	}

	char Spawn()
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

	void SetPartOfAShip()
	{
		isPartOfAShip = true;
	}

	void Shoot()
	{
		state = Shot;
	}
};

class Ship
{
public:
	int size;
	std::vector<Brick*> shipsBricks;

	Ship(std::vector<Brick*> bricksForShip, int size = 1)
	{
		this->size = size;
		shipsBricks = bricksForShip;

		for (int i = 0; i < size; i++)
		{
			shipsBricks[i]->SetPartOfAShip();
		}
	}
};

class Board
{
public:
	bool isGameRunning;
	int size;
	std::vector<Brick> bricks;
	std::vector<Brick*> reveledBricks;
	std::vector<Ship> ships;

	Board(int size)
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

	void ShootBrickAndSpawnBoard(int xBrick, int yBrick)
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

	void SetShips()
	{
		SetShip(3);
		SetShip(3);
		SetShip(2);
		SetShip(2);
		SetShip(2);
		SetShip(1);
		SetShip(1);
	}

	void SetShip(int size)
	{
		std::vector<Brick*> bricksForShips;
		std::random_device device;
		std::mt19937 generator(device());

		if (size != 1)
		{
			std::uniform_int_distribution<int> distribution(0, (this->size * this->size) - 1);

			int random = distribution(generator);

			switch (random % 2)
			{
			case 0: // horizontal
			{
				Brick* brick;
				std::vector<Brick*> chosenBricks;
				distribution = std::uniform_int_distribution<int>(0, (this->size * this->size) - 1);
				bool isBrickOccupied;

				do
				{
					chosenBricks.clear();

					random = distribution(generator);
					int rightSideDistance = this->size - (random % this->size); // how far away from right side

					while (rightSideDistance < size)
					{
						random = distribution(generator);
						rightSideDistance = this->size - (random % this->size);
					}

					brick = &bricks[random];
					chosenBricks.push_back(brick);

					int countBricks = size - 1;
					isBrickOccupied = false;

					while (countBricks > 0)
					{
						int indexToRight = random + countBricks;
						if (bricks[indexToRight].isPartOfAShip)
							isBrickOccupied = true;

						chosenBricks.push_back(&bricks[indexToRight]);
						countBricks--;
					}

				} while (brick->isPartOfAShip || isBrickOccupied);

				for (int i = 0; i < chosenBricks.size(); i++)
				{
					chosenBricks[i]->SetPartOfAShip();
					bricksForShips.push_back(chosenBricks[i]);
				}

				Ship ship = Ship(bricksForShips);
				ships.push_back(ship);
			}break;
			case 1: // vertical
			{
				Brick* brick;
				std::vector<Brick*> chosenBricks;
				distribution = std::uniform_int_distribution<int>(0, ((this->size * this->size) - 1) - (this->size * (size - 1))); //maxindex - rozmiar tablicy * rozmiar statku - 1
				bool isBrickOccupied;

				do
				{
					chosenBricks.clear();

					random = distribution(generator);
					brick = &bricks[random];
					chosenBricks.push_back(brick);

					int countBricks = size - 1;
					isBrickOccupied = false;

					while (countBricks > 0)
					{
						int indexBelow = random + ((this->size) * countBricks);
						if (bricks[indexBelow].isPartOfAShip)
							isBrickOccupied = true;

						chosenBricks.push_back(&bricks[indexBelow]);
						countBricks--;
					}

				} while (brick->isPartOfAShip || isBrickOccupied);

				for (int i = 0; i < chosenBricks.size(); i++)
				{
					chosenBricks[i]->SetPartOfAShip();
					bricksForShips.push_back(chosenBricks[i]);
				}

				Ship ship = Ship(bricksForShips);
				ships.push_back(ship);
			}break;
			}
			
		}
		else
		{

			std::uniform_int_distribution<int> distribution(0, (this->size * this->size) - 1);

			Brick* brick;

			do
			{
				int random = distribution(generator);
				brick = &bricks[random];
			} while (brick->isPartOfAShip);

			brick->SetPartOfAShip();
			bricksForShips.push_back(brick);

			Ship ship = Ship(bricksForShips);
			ships.push_back(ship);
		}
	}
};

int main()
{
	Board board = Board(6);

	int x, y;

	while (board.isGameRunning)
	{
		std::cout << "Enter X value: ";
		std::cin >> x;
		std::cout << "Enter Y value: ";
		std::cin >> y;

		board.ShootBrickAndSpawnBoard(x, y);
	}
	std::cout << "Congratulations you've won :D" << std::endl;
}