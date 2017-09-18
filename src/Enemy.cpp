#include "stdafx.h"
#include "Enemy.h"
#include "PowerUp.h"
#include "Game.h"

Enemy::Enemy(int createType)
{
	if (createType == STANDARD)
	{
		Load("res/img/Enemy_Standard.png");
		type = STANDARD;
		health = 4.0f;
		points = 1000;
		damage = 5.0f;
		originalVelocity = 200.0f;
	}
	else if (createType == SCOUT)
	{
		Load("res/img/Enemy_Scout.png");
		type = SCOUT;
		health = 1.0f;
		points = 2000;
		damage = 10.0f;
		originalVelocity = 500.0f;
	}
	else if (createType == TANK)
	{
		Load("res/img/Enemy_Tank.png");
		type = TANK;
		health = 10.0f;
		points = 4000;
		damage = 20.0f;
		originalVelocity = 50.0f;
	}

	assert(IsLoaded());
	currentVelocity = originalVelocity;
	GetSprite().setOrigin(GetSprite().getGlobalBounds().width / 2, GetSprite().getGlobalBounds().height / 2);
}

Enemy::~Enemy() {}

void Enemy::Update(float elapsedTime)
{
	GetSprite().move(0, currentVelocity * elapsedTime);
	if (GetSprite().getPosition().y > (Game::screen_Height - PlayArea::HUD.getGlobalBounds().height))
	{
		PlayerAvatar* player = Game::ReturnPlayer();
		player->GetHealth() -= damage;
		Vanish();
	}

	currentVelocity = originalVelocity;
}

void Enemy::Draw(sf::RenderWindow& window)
{
	Game_Object::Draw(window);
}

void Enemy::Reset()
{
	Vanish();
}

float& Enemy::GetHealth()
{
	return health;
}

float& Enemy::GetCurrentVelocity()
{
	return currentVelocity;
}

float Enemy::GetOriginalVelocity()
{
	return originalVelocity;
}

void Enemy::Damaged(float damage)
{
	health -= damage;

	if (health == 0.0f)
	{
		srand(time(NULL));
		switch (type)
		{
		case STANDARD:
		{
			int random = std::rand() % 5;
			if (random == 0)
			{
				PowerUp* power = new PowerUp(STANDARD);
				std::map<std::string, Game_Object*>::iterator result = Game::GetGOM().GetAllObjects().find("Powerup_Standard");
				if (result == Game::GetGOM().GetAllObjects().end())
					Game::GetGOM().Add("Powerup_Standard", power);
			}
			break;
		}
		case SCOUT:
		{
			int random = std::rand() % 10;
			if (random == 0)
			{
				PowerUp* power = new PowerUp(SCOUT);
				std::map<std::string, Game_Object*>::iterator result = Game::GetGOM().GetAllObjects().find("Powerup_Scout");
				if (result == Game::GetGOM().GetAllObjects().end())
					Game::GetGOM().Add("Powerup_Scout", power);
			}
			break;
		}
		case TANK:
		{
			int random = std::rand() % 10;
			if (random == 0)
			{
				PowerUp* power = new PowerUp(TANK);
				std::map<std::string, Game_Object*>::iterator result = Game::GetGOM().GetAllObjects().find("Powerup_Tank");
				if (result == Game::GetGOM().GetAllObjects().end())
					Game::GetGOM().Add("Powerup_Tank", power);
			}
			break;
		}
		}

		Game::GetYourScore() += points;
		Vanish();
	}
}

