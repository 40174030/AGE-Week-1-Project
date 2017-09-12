#include "stdafx.h"
#include "PlayerShip.h"
#include "Game.h"

PlayerShip::PlayerShip()
{
	Load("res/img/spaceship1.png");
	assert(IsLoaded());

	GetSprite().setOrigin(GetSprite().getLocalBounds().width / 2, GetSprite().getLocalBounds().height / 2);
	SetPosition((Game::screen_Width / 2), (Game::screen_Height / 2));
}

PlayerShip::~PlayerShip() {}

void PlayerShip::Draw(sf::RenderWindow& window)
{
	Game_Object::Draw(window);
}

void PlayerShip::Reset()
{

}

void PlayerShip::Update(float elapsedTime)
{

}