#pragma once
class Brick
{
public:
	int x, y;
	bool isPartOfAShip;

	enum BrickState
	{
		Hidden,
		Showed,
		Shot,
	};

	BrickState state;

	Brick();
	Brick(int x, int y);

	char Spawn();

	void SetPartOfAShip();
	void Shoot();
	void Show();
	void Hide();
};