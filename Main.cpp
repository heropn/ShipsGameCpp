#include <iostream>
#include "Brick.h"
#include "Ship.h"
#include "Board.h"


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