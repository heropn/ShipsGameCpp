#pragma once
#include "Brick.h"

class Board
{
public:
	std::vector<Brick> bricks;

	Board();
	Board(size_t size);

	void SpawnBoard();
	void ShowAllBricks();
	void HideAllBricks();

private:
	size_t size;
};