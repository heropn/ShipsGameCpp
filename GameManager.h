#pragma once
#include "Board.h"
#include "Ship.h"
#include <string>

class GameManager
{
public:
	Board firstBoard, secondBoard;
	bool isGameRunning = false;
	bool versusComputer = false;
	int boardSize;
	int numberOfPlayers;
	float waitShowTimeSeconds = 1.0f;
	float waitBetweenPlayersSeconds = 1.0f;
	std::vector<Ship> firstPlayerShips, secondPlayersShips;

	GameManager();

	void Play();

	void SetShips(Board& board, std::vector<Ship>& playerShipsVector);
	void SetShip(Board& board, std::vector<Ship>& playerShipsVector, int shipSize);
	void Wait(float seconds);
	void Move(Board& board, std::vector<Ship>& ships, std::string playerName, bool isComputer = false);

	bool ShootBrick(Board& board, int xBrick, int yBrick, Brick& emptyBrickPtr);
	bool AreAllShipsDestroyed(std::vector<Ship>& playerShips);
	bool CheckIfBrickConnectToAnyShip(Board& board, int brickIndex);
};