#pragma once
#include "Game_Object.h"

class PowerUp : public Game_Object
{
public:
	PowerUp(int enemnyType);
	~PowerUp();

	void Update(float elapsedTime);
	void Draw(sf::RenderWindow& window);
	int GetPowerType();

private:
	int powerType;
	float duration;
	sf::Clock countup;
};