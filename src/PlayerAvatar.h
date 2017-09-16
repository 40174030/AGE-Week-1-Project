#pragma once
#include "Game_Object.h"

class PlayerAvatar : public Game_Object
{
public:
	PlayerAvatar();
	~PlayerAvatar();

	void Update(float elapsedTime);
	void Draw(sf::RenderWindow& window);
	void Reset();

private:
	sf::Clock fireClock;
	float velocity;
	long projectilesFired;
	float sinceLastFire;
	const float fireRate = 0.3f;
	const float max_velocity = 1500.0f;
};