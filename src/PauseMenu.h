#pragma once

class PauseMenu
{
public:
	enum MenuOptions
	{
		Resume_Game,
		Back_to_Main,
		Close_Window
	};

	MenuOptions Show(sf::RenderWindow& window);

private:
	sf::Sprite sprite;
	sf::RectangleShape highlight;

	// Set up highlight regions
	// "Resume Game" co-ordinates
	const sf::Vector2f highlightResume = sf::Vector2f(575.0f, 385.0f);
	// "Main Menu" co-ordinates
	const sf::Vector2f highlightBackTo = sf::Vector2f(575.0f, 546.0f);

	MenuOptions selection;
	MenuOptions GetMenuResponse(sf::RenderWindow& window);
	void moveHighlight(sf::RenderWindow& window, MenuOptions newSelection);
};