#pragma once
#include "Board.h"
#include "Ship.h"
#include <string>

class GameManager
{
public:
	void Play();
	void DisplayRules();

private:
	Board firstBoard, secondBoard;
	Brick* lastShootedComputerBrick = nullptr;
	int lastShootedY{}, lastShootedX{};
	bool isGameRunning = false;
	bool versusComputer = false;
	int boardSize{};
	int numberOfPlayers{};
	int waitShowTimeSeconds = 1;
	int waitBetweenPlayersSeconds = 1;
	std::vector<Ship> firstPlayerShips, secondPlayersShips;

	void SetShips(Board& board, std::vector<Ship>& playerShipsVector, const std::string& playerName, bool isAutomatic);
	void SetShipAutomaticlly(Board& board, std::vector<Ship>& playerShipsVector, int shipSize);
	void SetShipByPlayer(Board& board, std::vector<Ship>& playerShipsVector, int shipSize, const std::string& playerName);
	void Wait(int seconds);
	void Move(Board& board, std::vector<Ship>& ships, const std::string& playerName);
	void MoveComputer(Board& board, std::vector<Ship>& ships, const std::string& computerName);
	void GetCoordinates(int& x, int& y);

	bool ShootBrick(Board& board, int xBrick, int yBrick, Brick*& emptyBrickPtr);
	bool AreAllShipsDestroyed(std::vector<Ship>& playerShips);
	bool CheckIfBrickConnectToAnyShip(Board& board, int brickIndex, bool computerMode = false);
	bool IsShipDestroyed(std::vector<Ship>& playerShips, Brick* shipsBrick, Ship*& emptyShipPtr);
};