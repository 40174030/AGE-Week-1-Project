#include "stdafx.h"
#include "PlayerAvatar.h"
#include "Game.h"

PlayerAvatar::PlayerAvatar()
{
	Load("res/img/Avatar.png");
	assert(IsLoaded());

	if (!Game::FullscreenCheck())
	{
		sf::Vector2f originalScale = GetSprite().getScale();
		sf::Vector2f downscaleVector = sf::Vector2f(Game::downscale, Game::downscale);
		GetSprite().scale(originalScale.x * downscaleVector.x, originalScale.y * downscaleVector.y);
	}

	GetSprite().setOrigin(GetSprite().getGlobalBounds().width / 2, GetSprite().getGlobalBounds().height / 2);

	if (Game::FullscreenCheck())
	{
		SetPosition((Game::fullscreen_Width / 2), (Game::fullscreen_Height / 2));
	}
	else
	{
		SetPosition((Game::windowed_Width / 2), (Game::windowed_Height / 2));
	}
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