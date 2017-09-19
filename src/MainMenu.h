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
	void MoveUp();
	void MoveDown();

	bool keyHeld = false;
	bool eligibleKeyPressed = false;

	sf::Sprite sprite;
	sf::RectangleShape highlight;

	// Set up highlight regions
	// "Play Game" co-ordinates
	const sf::Vector2f highlightPlayGame = sf::Vector2f(575.0f, 222.0f);
	// "How to Play" co-ordinates
	const sf::Vector2f highlightHowToPlay = sf::Vector2f(575.0f, 385.0f);
	// "Settings" co-ordinates
	const sf::Vector2f highlightSettings = sf::Vector2f(575.0f, 546.0f);
	// "Quit Game" co-ordinates
	const sf::Vector2f highlightQuitGame = sf::Vector2f(575.0f, 705.0f);

	MenuOptions selection;
	MenuOptions GetMenuResponse(sf::RenderWindow& window);
	void moveHighlight(sf::RenderWindow& window, MenuOptions newSelection);
};