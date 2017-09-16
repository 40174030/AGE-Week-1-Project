#pragma once
#include "Game_Object.h"

class PlayerProjectile : public Game_Object
{
public:
	PlayerProjectile();
	~PlayerProjectile();

	void Update(float elapsedTime);
	void Draw(sf::RenderWindow& window);

private:
	float damage;
	const float velocity = 1500.0f;
};