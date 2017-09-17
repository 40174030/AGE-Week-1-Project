#include "stdafx.h"
#include "PowerUp.h"
#include "Game.h"

PowerUp::PowerUp(int enemyType)
{
	countup.restart();
	powerType = enemyType;
	switch (powerType)
	{
	case STANDARD: { duration = 1.0f; break; }
	case SCOUT: { duration = 5.0f; break; }
	case TANK: { duration = 7.0f; break; }
	}
}

PowerUp::~PowerUp() {}

void PowerUp::Update(float elapsedTime)
{
	if (countup.getElapsedTime().asSeconds() >= duration)
	{
		Vanish();
	}
}

void PowerUp::Draw(sf::RenderWindow & window)
{
	Game_Object::Draw(window);
}

int PowerUp::GetPowerType()
{
	return powerType;
}
