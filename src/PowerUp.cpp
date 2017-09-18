#include "stdafx.h"
#include "PowerUp.h"
#include "Game.h"

PowerUp::PowerUp(int enemyType)
{
	powerType = enemyType;
	switch (powerType)
	{
	case STANDARD: { duration = 1.0f; break; }
	case SCOUT: { duration = 5.0f; break; }
	case TANK: { duration = 7.0f; break; }
	}
	powerRemaining = duration;
}

PowerUp::~PowerUp() {}

void PowerUp::Update(float elapsedTime)
{
	if (powerRemaining <= 0.0f)
	{
		PlayerAvatar* player = Game::ReturnPlayer();
		switch (GetPowerType())
		{
		case STANDARD: { player->DeactivateRecovery(); break; }
		case SCOUT: { player->DeactivateSloMo(); break; }
		case TANK: { player->DeactivateSuperFire(); break; }
		}
		Vanish();
	}
	else
		powerRemaining -= frameTime.getElapsedTime().asSeconds();
	frameTime.restart();
}

void PowerUp::Draw(sf::RenderWindow & window)
{
	Game_Object::Draw(window);
}

void PowerUp::Reset()
{
	Vanish();
}

int PowerUp::GetPowerType()
{
	return powerType;
}
