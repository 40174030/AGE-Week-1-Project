#pragma once

class MainMenu
{
public:
	enum MenuOptions 
	{
		Play_Game,
		How_to_Play,
		Settings,
		Quit_Game
	};

	sf::RectangleShape highlight; 

	// Set up highlight regions
	// "Play Game" co-ordinates

	// "How to Play" co-ordinates

	// "Settings" co-ordinates

	// "Quit Game" co-ordinates


	MenuOptions Show(sf::RenderWindow& window);

private:
	MenuOptions selection;
	MenuOptions GetMenuResponse(sf::RenderWindow& window);
};