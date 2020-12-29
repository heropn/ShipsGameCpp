#pragma once
class Brick
{
public:
	unsigned int x, y;
	bool isPartOfAShip;

	enum class State
	{
		Hidden,
		Showed,
		Shot,
	};

	State state;

	Brick();
	Brick(unsigned int x, unsigned int y);

	char Spawn();

	void SetPartOfAShip();
	void Shoot();
	void Show();
	void Hide();
};