#include "stdafx.h"
#include "PlayerAvatar.h"
#include "Game.h"

PlayerAvatar::PlayerAvatar()
{
	Load("res/img/spaceship1.png");
	assert(IsLoaded());

	GetSprite().setOrigin(GetSprite().getLocalBounds().width / 2, GetSprite().getLocalBounds().height / 2);
	SetPosition((Game::screen_Width / 2), (Game::screen_Height / 2));
}

PlayerAvatar::~PlayerAvatar() {}

void PlayerAvatar::Draw(sf::RenderWindow& window)
{
	Game_Object::Draw(window);
}

void PlayerAvatar::Reset()
{

}

void PlayerAvatar::Update(float elapsedTime)
{

}