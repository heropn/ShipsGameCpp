#pragma once
#include "Board.h"
#include "Ship.h"
#include <string>

class GameManager
{
public:
	void Play();
	GameManager();

private:
	Board firstBoard, secondBoard;
	bool isGameRunning = false;
	bool versusComputer = false;
	size_t boardSize;
	size_t numberOfPlayers;
	float waitShowTimeSeconds = 1.0f;
	float waitBetweenPlayersSeconds = 1.0f;
	std::vector<Ship> firstPlayerShips, secondPlayersShips;

	void SetShips(Board& board, std::vector<Ship>& playerShipsVector, const std::string& playerName, bool isAutomatic);
	void SetShipAutomaticlly(Board& board, std::vector<Ship>& playerShipsVector, int shipSize);
	void SetShipByPlayer(Board& board, std::vector<Ship>& playerShipsVector, int shipSize, const std::string& playerName);
	void Wait(float seconds);
	void Move(Board& board, std::vector<Ship>& ships, const std::string& playerName, bool isComputer = false);

	bool ShootBrick(Board& board, int xBrick, int yBrick, Brick*& emptyBrickPtr);
	bool AreAllShipsDestroyed(std::vector<Ship>& playerShips);
	bool CheckIfBrickConnectToAnyShip(Board& board, int brickIndex);
};