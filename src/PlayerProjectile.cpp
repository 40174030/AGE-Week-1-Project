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
}

PlayerProjectile::~PlayerProjectile(){}

void PlayerProjectile::Draw(sf::RenderWindow & window)
{
	Game_Object::Draw(window);
}

void PlayerProjectile::Update(float elapsedTime)
{
	GetSprite().move(0, -velocity * elapsedTime);
	if (GetSprite().getPosition().y < 0.0f)
	{
		Vanish();
	}
}
