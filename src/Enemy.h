#pragma once
#include "Game_Object.h"

class Enemy : public Game_Object
{
public:
	Enemy(int createType);
	~Enemy();

	void Update(float elapsedTime);
	void Draw(sf::RenderWindow& window);
	void Reset();

	float& GetHealth();
	float& GetCurrentVelocity();
	float GetOriginalVelocity();
	void Damaged(float damage);

private:
	int type;
	int ID_suffix;
	float health;
	float currentVelocity;
	float originalVelocity;
};