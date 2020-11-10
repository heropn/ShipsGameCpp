#pragma once

class Board
{
public:
	bool isGameRunning;
	int size;
	std::vector<Brick> bricks;
	std::vector<Brick*> reveledBricks;
	std::vector<Ship> ships;

	Board(int size);

	void ShootBrickAndSpawnBoard(int xBrick, int yBrick);
	void SetShips();
	void SetShip(int shipSize);

	bool CheckIfBrickConnectToAnyShip(int brickIndex);
};