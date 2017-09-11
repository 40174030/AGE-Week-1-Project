#include "stdafx.h"
#include "MainMenu.h"

MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& window)
{
	// Load menu image from file
	sf::Texture image;
	if (image.loadFromFile("res/img/MainMenu_Temp.png") != true)
	{
		throw std::invalid_argument("FAILED TO LOAD: MainMenu");
		return Exit;
	}
	sf::Sprite sprite(image);

	//// Set up clickable regions
	//// Play menu item co-ordinates
	//MenuItem playButton;
	//playButton.rect = sf::IntRect(0, 145, 1023, 230);
	//playButton.action = Play;

	//// Exit menu item coordinates
	//MenuItem exitButton;
	//exitButton.rect = sf::IntRect(0, 383, 1023, 180);
	//exitButton.action = Exit;

	//menuItems.push_back(playButton);
	//menuItems.push_back(exitButton);

	window.draw(sprite);
	window.display();

	return GetMenuResponse(window);
}

MainMenu::MenuResult MainMenu::HandleClick(int x, int y)
{
	std::list<MenuItem>::iterator it;

	for (it = menuItems.begin(); it != menuItems.end(); it++)
	{
		sf::IntRect menuItemRect = (*it).rect;
		if ((*it).rect.contains(x, y))
		{
			return (*it).action;
		}
	}
	return Nothing;
}

MainMenu::MenuResult MainMenu::GetMenuResponse(sf::RenderWindow& window)
{
	sf::Event menuEvent;

	while (true)
	{
		while (window.pollEvent(menuEvent))
		{
			if (menuEvent.type == sf::Event::MouseButtonPressed)
				return HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
			if (menuEvent.type == sf::Event::Closed)
				return Exit;
		}
	}
}