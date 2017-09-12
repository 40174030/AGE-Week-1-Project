#pragma once
#include "Game_Object.h"

class PlayerShip : public Game_Object
{
public:
	PlayerShip();
	~PlayerShip();

	void Update(float elapsedTime);
	void Draw(sf::RenderWindow& window);
	void Reset();
};