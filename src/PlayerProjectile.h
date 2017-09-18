#pragma once
#include "Game_Object.h"

class PlayerProjectile : public Game_Object
{
public:
	PlayerProjectile();
	~PlayerProjectile();

	void Update(float elapsedTime);
	void Draw(sf::RenderWindow& window);
	void Reset();

private:
	float damage;
	float velocity;
	const float originalVelocity = -1500.0f;
};