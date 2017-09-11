#include "stdafx.h"
#include "Game_ObjectManager.h"
#include "Game.h"

Game_ObjectManager::Game_ObjectManager() {}

Game_ObjectManager::~Game_ObjectManager()
{
	std::for_each(game_objects.begin(), game_objects.end(), Game_ObjectDeallocator());
}

void Game_ObjectManager::Add(std::string name, Game_Object* gameObject)
{
	game_objects.insert(std::pair<std::string, Game_Object*>(name, gameObject));
}

void Game_ObjectManager::Remove(std::string name)
{
	std::map<std::string, Game_Object*>::iterator results = game_objects.find(name);
	if (results != game_objects.end())
	{
		delete results->second;
		game_objects.erase(results);
	}
}

Game_Object* Game_ObjectManager::Get(std::string name) const
{
	std::map<std::string, Game_Object*>::const_iterator results = game_objects.find(name);
	if (results == game_objects.end())
		return NULL;
	return results->second;
}

int Game_ObjectManager::GetObjectCount() const
{
	return game_objects.size();
}

void Game_ObjectManager::DrawAll(sf::RenderWindow& renderWindow)
{
	std::map<std::string, Game_Object*>::const_iterator itr = game_objects.begin();
	while (itr != game_objects.end())
	{
		itr->second->Draw(renderWindow);
		itr++;
	}
}

void Game_ObjectManager::UpdateAll()
{
	std::map<std::string, Game_Object*>::const_iterator itr = game_objects.begin();
	float timeDelta = clock.restart().asSeconds();

	while (itr != game_objects.end())
	{
		itr->second->Update(timeDelta);
		itr++;
	}
}

void Game_ObjectManager::ResetAll()
{
	std::map<std::string, Game_Object*>::const_iterator itr = game_objects.begin();
	while (itr != game_objects.end())
	{
		itr->second->Reset();
		itr++;
	}
}

sf::Clock& Game_ObjectManager::GetClock()
{
	return clock;
}