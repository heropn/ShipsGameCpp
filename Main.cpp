#include "Brick.h"
#include "Ship.h"
#include "Board.h"
#include "GameManager.h"

int main()
{
	GameManager game = GameManager(3);
	game.Play();
}