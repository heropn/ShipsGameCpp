#pragma once
#include "Board.h"
#include "Ship.h"

class GameManager
{
public:
	Board firstBoard, secondBoard;
	bool isGameRunning = false;
	bool versusComputer = false;
	int boardSize;
	int numberOfPlayers;
	int waitShowTimeSeconds = 1;
	int waitBetweenPlayersSeconds = 1;
	std::vector<Ship> firstPlayerShips, secondPlayersShips;

	GameManager();

	void Play();
	bool ShootBrick(Board& board, int xBrick, int yBrick);
	void SetShips(Board& board, std::vector<Ship>& playerShipsVector);
	void SetShip(Board& board, std::vector<Ship>& playerShipsVector, int shipSize);
	void Wait(int seconds);
	
	bool AreAllShipsDestroyed(std::vector<Ship>& playerShips);
	bool CheckIfBrickConnectToAnyShip(Board& board, int brickIndex);
};