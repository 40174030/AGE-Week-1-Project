#include "stdafx.h"
#include "PlayerAvatar.h"
#include "PlayerProjectile.h"
#include "Game.h"

PlayerAvatar::PlayerAvatar() : projectilesFired(0), velocity(0.0f), sinceLastFire(0.0f)
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
	fireClock.restart().asSeconds();
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

std::map<std::string, Game_Object*>::iterator FindPrefix(std::map<std::string, Game_Object*>& objectList, std::string prefix)
{
	std::map<std::string, Game_Object*>::iterator i = objectList.lower_bound(prefix);
	if (i != objectList.end()) {
		const std::string& key = i->first;
		if (key.compare(0, prefix.size(), prefix) == 0)
			return i;
	}
	return objectList.end();
}

void PlayerAvatar::Update(float elapsedTime)
{
	sinceLastFire += fireClock.getElapsedTime().asSeconds();

	float boundaryLeft = PlayArea::lanes[PlayArea::GetLeftmostLane()].getGlobalBounds().left;
	float boundaryRight = PlayArea::lanes[PlayArea::GetRightmostLane()].getPosition().x + 
						  PlayArea::lanes[PlayArea::GetRightmostLane()].getGlobalBounds().width;
	
	// MOVEMENT
	sf::Vector2f pos = this->GetPosition();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
	{
		if (pos.x < (boundaryLeft + GetSprite().getGlobalBounds().width / 2))
			velocity = 0.0f;
		else
			velocity = -max_velocity;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
	{
		if (pos.x > (boundaryRight - GetSprite().getLocalBounds().width / 2))
			velocity = 0.0f;
		else
			velocity = max_velocity;
	}

	else
	{
		velocity = 0.0f;
	}

	GetSprite().move(velocity * elapsedTime, 0);

	// FIRING
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (sinceLastFire >= fireRate)
		{
			PlayerProjectile* proj = new PlayerProjectile();
			projectilesFired++;
			Game::GetGOM().Add("Projectile" + projectilesFired, proj);
			sinceLastFire = 0.0f;
			fireClock.restart().asSeconds();
		}
	}
}
