#pragma once
#include <list>

class MainMenu
{
public:
	enum MenuResult { Nothing, Exit, Play };

	struct MenuItem
	{
	public:
		sf::IntRect rect;
		MenuResult action;
	};

	MenuResult Show(sf::RenderWindow& window);

private:
	MenuResult GetMenuResponse(sf::RenderWindow& window);
	MenuResult HandleClick(int x, int y);
	std::list<MenuItem> menuItems;
};