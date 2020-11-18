#include <iostream>
#include "Brick.h"
#include "Ship.h"
#include "Board.h"
#include "GameManager.h"

int main()
{
	do
	{
		GameManager game;
		game.Play();

		system("CLS");

		std::cout << "Do you want to play again?" << std::endl << "Yes: type 1	No: type 0" << std::endl;
		std::string input = "-";

		while (input != "1" && input != "0")
		{
			std::cin >> input;

			if (input != "1" && input != "0")
			{
				std::cout << "Wrong value" << std::endl;
				continue;
			}
		}

		if (input == "0")
			break;

	} while (true);

	system("pause");
}