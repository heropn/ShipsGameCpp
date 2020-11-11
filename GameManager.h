#pragma once
#include "Board.h"
#include "Ship.h"

class GameManager
{
public:
	Board firstBoard, secondBoard;
	bool isGameRunning;
	int boardSize;
	int numberOfPlayers;
	std::vector<Ship> firstPlayerShips, secondPlayersShips;

	GameManager(int boardSize);

	void Play();
	void ShootBrickAndSpawnBoard(Board& board, int xBrick, int yBrick);
	void SetShips(Board& board);
	void SetShip(Board& board, int shipSize);
	bool CheckIfShipGotDestoyed();

	bool CheckIfBrickConnectToAnyShip(Board& board, int brickIndex);
};