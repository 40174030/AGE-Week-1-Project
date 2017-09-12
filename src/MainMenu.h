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

	MenuOptions Show(sf::RenderWindow& window);

private:
	sf::Sprite sprite;
	sf::RectangleShape highlight;

	// Set up highlight regions
	// "Play Game" co-ordinates
	sf::Vector2f highlightPlayGame = sf::Vector2f(575.0f, 222.0f);
	// "How to Play" co-ordinates
	sf::Vector2f highlightHowToPlay = sf::Vector2f(575.0f, 222.0f);
	// "Settings" co-ordinates
	sf::Vector2f highlightSettings = sf::Vector2f(575.0f, 222.0f);
	// "Quit Game" co-ordinates
	sf::Vector2f highlightQuitGame = sf::Vector2f(575.0f, 222.0f);

	MenuOptions selection;
	MenuOptions GetMenuResponse(sf::RenderWindow& window);
};