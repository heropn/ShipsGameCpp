#pragma once
class Brick
{
public:
	unsigned int x, y;
	bool isPartOfAShip;

	enum class BrickState
	{
		Hidden,
		Showed,
		Shot,
	};

	BrickState state;

	Brick();
	Brick(unsigned int x, unsigned int y);

	char Spawn();

	void SetPartOfAShip();
	void Shoot();
	void Show();
	void Hide();
};