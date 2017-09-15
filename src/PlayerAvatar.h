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
	bool keyHeld;
	bool eligibleKeyPressed;
	float velocity;
	const float max_velocity = 1500.0f;
};