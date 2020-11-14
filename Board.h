#pragma once
#include "Brick.h"

class Board
{
public:
	std::vector<Brick> bricks;

	Board();
	Board(int size);

	void SpawnBoard();
	void ShowAllBricks();
	void HideAllBricks();

private:
	int size;
};