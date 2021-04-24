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

		system("cls");
		std::cout << "1. Graj" << std::endl;
		std::cout << "2. Zasady gry" << std::endl;
		std::cout << "3. Wyjdz" << std::endl;

		std::string input = "";

		while (input != "1" && input != "2" && input != "3")
		{
			std::cin >> input;

			if (input == "1")
			{
				system("cls");
				game.Play();
				system("pause");
			}
			else if (input == "2")
			{
				system("cls");
				game.DisplayRules();
				system("pause");
			}
			else if (input == "3")
			{
				return 0;
			}
			else
			{
				std::cout << "Zla wartosc!" << std::endl;
			}
		}
	} while (true);
}