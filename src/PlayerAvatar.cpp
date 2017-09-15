#include "stdafx.h"
#include "PlayerAvatar.h"
#include "Game.h"

PlayerAvatar::PlayerAvatar() : velocity(0.0f)
{
	Load("res/img/Avatar.png");
	assert(IsLoaded());

	//if (!Game::FullscreenCheck())
	//{
	//	sf::Vector2f originalScale = GetSprite().getScale();
	//	sf::Vector2f downscaleVector = sf::Vector2f(Game::downscale, Game::downscale);
	//	GetSprite().scale(originalScale.x * downscaleVector.x, originalScale.y * downscaleVector.y);
	//}

	GetSprite().setOrigin(GetSprite().getGlobalBounds().width / 2, GetSprite().getGlobalBounds().height / 2);
	Reset();

	keyHeld = false;
	eligibleKeyPressed = false;
}

PlayerAvatar::~PlayerAvatar() {}

void PlayerAvatar::Draw(sf::RenderWindow& window)
{
	Game_Object::Draw(window);
}

void PlayerAvatar::Reset()
{
	SetPosition((Game::screen_Width / 2), (Game::screen_Height - GetSprite().getGlobalBounds().height / 2));
	//if (Game::FullscreenCheck())
	//{
	//	SetPosition((Game::fullscreen_Width / 2), (Game::fullscreen_Height - GetSprite().getGlobalBounds().height / 2));
	//}
	//else
	//{
	//	SetPosition((Game::windowed_Width / 2), (Game::windowed_Height - GetSprite().getGlobalBounds().height / 2));
	//}
}

void PlayerAvatar::Update(float elapsedTime)
{
	if (!keyHeld)
	{
		sf::Vector2f pos = this->GetPosition();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
		{
			eligibleKeyPressed = true;
			keyHeld = true;
			if (pos.x < GetSprite().getGlobalBounds().width / 2)
				velocity = 0.0f;
			else
				velocity = -max_velocity;
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
		{
			eligibleKeyPressed = true;
			keyHeld = true;
			if (pos.x > (Game::screen_Width - GetSprite().getLocalBounds().width / 2))
				velocity = 0.0f;
			else
				velocity = max_velocity;
		}
	}
	
	if (eligibleKeyPressed)
	{
		eligibleKeyPressed = false;
		keyHeld = false;
	}
	else
	{
		velocity = 0.0f;
	}

	GetSprite().move(velocity * elapsedTime, 0);
}