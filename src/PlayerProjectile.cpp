#include "stdafx.h"
#include "PlayerProjectile.h"
#include "Game.h"


PlayerProjectile::PlayerProjectile() : damage(1.0f)
{
	Load("res/img/AvatarProjectile.png");
	assert(IsLoaded());
	GetSprite().setOrigin(GetSprite().getGlobalBounds().width / 2, 
						  GetSprite().getGlobalBounds().height);
	SetPosition(Game::GetGOM().GetSingleObject("Player")->GetPosition().x, 
				Game::GetGOM().GetSingleObject("Player")->GetPosition().y);
	velocity = originalVelocity;
}

PlayerProjectile::~PlayerProjectile(){}

void PlayerProjectile::Draw(sf::RenderWindow & window)
{
	Game_Object::Draw(window);
}

void PlayerProjectile::Update(float elapsedTime)
{
	GetSprite().move(0, velocity * elapsedTime);

	if (GetSprite().getPosition().y < 0.0f)
	{
		Vanish();
	}
	
	std::map<std::string, Game_Object*>::iterator itr = Game::GetGOM().GetAllObjects().begin();
	while (itr != Game::GetGOM().GetAllObjects().end())
	{
		if (strstr(itr->first.c_str(), "Enemy"))
		{
			if (GetSprite().getGlobalBounds().intersects(itr->second->GetSprite().getGlobalBounds()))
			{
				ServiceLocator::GetAudio()->PlaySound("res/Hit_hurt2.wav");
				Enemy* enemy = static_cast<Enemy*>(Game::GetGOM().GetSingleObject(itr->first));
				enemy->Damaged(damage);
				if (enemy->GetHealth() == 0.0f)
					enemy->Vanish();
				Vanish();
			}
		}
		itr++;
	}

	velocity = originalVelocity;
}

void PlayerProjectile::Reset()
{
	Vanish();
}
