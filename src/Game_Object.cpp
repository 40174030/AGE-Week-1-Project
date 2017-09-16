#include "stdafx.h"
#include "Game_Object.h"

Game_Object::Game_Object() : isLoaded(false), vanished(false) {}

Game_Object::~Game_Object() {}

void Game_Object::Load(std::string filename)
{
	if (image.loadFromFile(filename) == false)
	{
		filename = "";
		isLoaded = false;
		std::cerr << "FAILED TO LOAD: GameObject" << std::endl;
	}
	else
	{
		filename = filename;
		sprite.setTexture(image);
		isLoaded = true;
	}
}

void Game_Object::Draw(sf::RenderWindow& renderWindow)
{
	if (isLoaded)
	{
		renderWindow.draw(sprite);
	}
}

void Game_Object::Update(float elapsedTime) {}

void Game_Object::Reset() {}

void Game_Object::SetPosition(float x, float y)
{
	if (isLoaded)
		sprite.setPosition(x, y);
}

sf::Vector2f Game_Object::GetPosition() const
{
	if (isLoaded)
		return sprite.getPosition();
	return sf::Vector2f();
}

sf::Sprite& Game_Object::GetSprite()
{
	return sprite;
}

bool Game_Object::IsLoaded() const
{
	return isLoaded;
}

void Game_Object::Vanish()
{
	vanished = true;
}

bool Game_Object::HasVanished() const
{
	return vanished;
}
//
//std::string Game_Object::GetFilename() const
//{
//	return filename;
//}

float Game_Object::GetHeight() const
{
	return sprite.getLocalBounds().height;
}

float Game_Object::GetWidth() const
{
	return sprite.getLocalBounds().width;
}