#pragma once
class SettingsMenu
{
public:
	enum MenuOptions
	{
		Full_HD,
		HD,
		SD,
		Back_to_Main,
		Quit_Game
	};

	SettingsMenu::MenuOptions Show(sf::RenderWindow& window);

private:
	void MoveUp();
	void MoveDown();

	bool keyHeld = false;
	bool buttonHeld = true;
	bool stickHeld = false;
	bool eligibleKeyPressed = false;

	sf::Sprite sprite;
	sf::RectangleShape highlight;

	// Set up highlight regions
	// "Play Game" co-ordinates
	const sf::Vector2f highlightFullHD = sf::Vector2f(575.0f, 222.0f);
	// "How to Play" co-ordinates
	const sf::Vector2f highlightHD = sf::Vector2f(575.0f, 385.0f);
	// "Settings" co-ordinates
	const sf::Vector2f highlightSD = sf::Vector2f(575.0f, 546.0f);
	// "Quit Game" co-ordinates
	const sf::Vector2f highlightBack = sf::Vector2f(575.0f, 705.0f);

	MenuOptions selection;
	MenuOptions GetMenuResponse(sf::RenderWindow& window);
	void moveHighlight(sf::RenderWindow& window, MenuOptions newSelection);
};