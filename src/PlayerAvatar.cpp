#include "stdafx.h"
#include "PlayerAvatar.h"
#include "PlayerProjectile.h"
#include "PowerUp.h"
#include "Game.h"

PlayerAvatar::PlayerAvatar() : health(100.0f), projectilesFired(0), 
							   velocity(0.0f), sinceLastFire(0.0f),
							   active_Recovery(false), active_SloMo(false), active_SuperFire(false)
{
	Load("res/img/Avatar.png");
	assert(IsLoaded());

	GetSprite().setOrigin(GetSprite().getGlobalBounds().width / 2, GetSprite().getGlobalBounds().height / 2);
	fireClock.restart();
}

PlayerAvatar::~PlayerAvatar() {}

void PlayerAvatar::Draw(sf::RenderWindow& window)
{
	Game_Object::Draw(window);
}

void PlayerAvatar::Reset()
{
	SetPosition((Game::screen_Width / 2), 
		(Game::screen_Height - GetSprite().getLocalBounds().height / 2) - PlayArea::HUD.getLocalBounds().height + 2.0f);
	GetSprite().setRotation(0.0f);
	health = 100.0f;
}

float& PlayerAvatar::GetHealth()
{
	return health;
}

bool PlayerAvatar::IsRecoveryActive()
{
	return active_Recovery;
}

bool PlayerAvatar::IsSloMoActive()
{
	return active_SloMo;
}

bool PlayerAvatar::IsSuperFireActive()
{
	return active_SuperFire;
}

void PlayerAvatar::DeactivateRecovery()
{
	active_Recovery = false;
}

void PlayerAvatar::DeactivateSloMo()
{
	active_SloMo = false;
}

void PlayerAvatar::DeactivateSuperFire()
{
	active_SuperFire = false;
}

void PlayerAvatar::Update(float elapsedTime)
{
	sinceLastFire = fireClock.getElapsedTime().asSeconds();

	// CHECK FOR POWERUPS
	std::map<std::string, Game_Object*>::iterator itr = Game::GetGOM().GetAllObjects().begin();
	while (itr != Game::GetGOM().GetAllObjects().end())
	{
		if (strstr(itr->first.c_str(), "Powerup"))
		{
			PowerUp* power = static_cast<PowerUp*>(Game::GetGOM().GetSingleObject(itr->first));
			int powerType = power->GetPowerType();

			switch (powerType)
			{
			case STANDARD:
			{
				if (health < 100.0f)
				{
					active_Recovery = true;
					health += 0.02f;
				}
				else if (health >= 100.0f)
					health = 100.0f;
				break;
			}
			case SCOUT:
			{
				active_SloMo = true;
				std::map<std::string, Game_Object*>::iterator itr = Game::GetGOM().GetAllObjects().begin();
				while (itr != Game::GetGOM().GetAllObjects().end())
				{
					if (strstr(itr->first.c_str(), "Enemy"))
					{
						Enemy* enemy = static_cast<Enemy*>(Game::GetGOM().GetSingleObject(itr->first));
						enemy->GetCurrentVelocity() = enemy->GetOriginalVelocity() / 8.0f;
					}
					itr++;
				}
				break;
			}
			case TANK:
			{
				active_SuperFire = true;
				fireRate_Current = fireRate_Original / 5.0f;
				break;
			}
			}
		}
		itr++;
	}
	
	// MOVEMENT
	if (sf::Joystick::isConnected(0))
	{
		float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
		float x2 = sf::Joystick::getAxisPosition(0, sf::Joystick::PovX);

		if (x > 15)
			MoveRight();
		else if (x < -15)
			MoveLeft();
		else if (x2 > 15)
			MoveRight();
		else if (x2 < -15)
			MoveLeft();
		else
			velocity = 0.0f;

		if (sf::Joystick::isButtonPressed(0, 0))
			FireWeapon();
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
			MoveLeft();
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
			MoveRight();
		else
			velocity = 0.0f;

		// FIRING
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			FireWeapon();
	}

	GetSprite().move(velocity * elapsedTime, 0);
	fireRate_Current = fireRate_Original;
}


void PlayerAvatar::MoveLeft()
{
	sf::Vector2f pos = this->GetPosition();
	float boundaryLeft = PlayArea::lanes[PlayArea::GetLeftmostLane()].getGlobalBounds().left;

	if (pos.x < (boundaryLeft + GetSprite().getLocalBounds().width / 2))
		velocity = 0.0f;
	else
	{
		velocity = -max_velocity;
		GetSprite().rotate(-1.0f);
	}
}


void PlayerAvatar::MoveRight()
{
	sf::Vector2f pos = this->GetPosition();
	float boundaryRight = PlayArea::lanes[PlayArea::GetRightmostLane()].getPosition().x +
		PlayArea::lanes[PlayArea::GetRightmostLane()].getGlobalBounds().width;

	if (pos.x > (boundaryRight - GetSprite().getLocalBounds().width / 2))
		velocity = 0.0f;
	else
	{
		velocity = max_velocity;
		GetSprite().rotate(1.0f);
	}
}


void PlayerAvatar::FireWeapon()
{
	if (sinceLastFire > fireRate_Current)
	{
		PlayerProjectile* proj = new PlayerProjectile();
		ServiceLocator::GetAudio()->PlaySound("res/Laser_Shoot4.wav");
		projectilesFired++;
		std::string projID = "Projectile" + std::to_string(projectilesFired);
		Game::GetGOM().Add(projID, proj);
		std::cout << projID << std::endl;
		sinceLastFire = 0.0f;
		fireClock.restart();
	}
}


