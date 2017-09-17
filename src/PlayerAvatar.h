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
	float health;
	float velocity;
	int projectilesFired;
	float sinceLastFire;
	float fireRate_Current;
	const float fireRate_Original = 0.2f;
	const float max_velocity = 1000.0f;
};