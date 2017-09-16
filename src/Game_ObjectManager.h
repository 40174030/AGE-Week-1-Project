#pragma once
#include "Game_Object.h"

class Game_ObjectManager
{
public:
	Game_ObjectManager();
	~Game_ObjectManager();

	void Add(std::string name, Game_Object* gameObject);
	void Remove(std::string name);
	int GetObjectCount() const;
	Game_Object* GetSingleObject(std::string name) const;
	std::map<std::string, Game_Object*>& GetAllObjects();

	void DrawAll(sf::RenderWindow& renderWindow);
	void UpdateAll();
	void ResetAll();

	sf::Clock& GetClock();

private:
	std::map<std::string, Game_Object*> game_objects;

	sf::Clock clock;

	struct Game_ObjectDeallocator
	{
		void operator()(const std::pair<std::string, Game_Object*>& p) const
		{
			delete p.second;
		}
	};
};