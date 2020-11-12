#pragma once
#include "Brick.h"

class Board
{
public:
	int size;
	std::vector<Brick> bricks;

	Board();
	Board(int size);

	void SpawnBoard();
	void ShowAllBricks();
	void HideAllBricks();
};