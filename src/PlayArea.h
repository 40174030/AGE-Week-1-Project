#pragma once
#include "Game_Object.h"

class PlayArea
{
public:
	void Setup();
	void Draw(sf::RenderWindow& window, int level);
	void Update(int level);
	void Reset();

private:
	sf::RectangleShape lanes[10];
};