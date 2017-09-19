#include "stdafx.h"
#include "PauseMenu.h"
#include "Game.h"

PauseMenu::MenuOptions PauseMenu::Show(sf::RenderWindow& window)
{
	selection = Resume_Game;

	// Load menu image from file
	sf::Texture image;

	if (image.loadFromFile("res/img/PauseMenu_Temp.png") != true)
	{
		throw std::invalid_argument("FAILED TO LOAD: PauseMenu");
		return Close_Window;
	}

	sprite.setTexture(image);

	highlight.setSize(sf::Vector2f(700.0f, 135.0f));
	highlight.setOutlineColor(sf::Color(255, 255, 0));
	highlight.setFillColor(sf::Color::Transparent);
	highlight.setOutlineThickness(10.0f);
	highlight.setPosition(highlightResume);

	window.draw(sprite);

	return GetMenuResponse(window);
}


void PauseMenu::moveHighlight(sf::RenderWindow& window, PauseMenu::MenuOptions newSelection)
{
	switch (newSelection)
	{
	case Resume_Game:
	{
		highlight.setPosition(highlightResume);
		break;
	}
	case Back_to_Main:
	{
		highlight.setPosition(highlightBackTo);
		break;
	}
	}
}

PauseMenu::MenuOptions PauseMenu::GetMenuResponse(sf::RenderWindow& window)
{
	sf::Event menuEvent;

	while (true)
	{
		window.clear();
		window.draw(sprite);
		window.draw(highlight);
		window.display();

		while (window.pollEvent(menuEvent))
		{
			if (menuEvent.type == sf::Event::EventType::KeyPressed
				&& menuEvent.key.code == sf::Keyboard::Escape)
				return Resume_Game;

			if (menuEvent.type == sf::Event::EventType::KeyReleased
				&& eligibleKeyPressed)
			{
				eligibleKeyPressed = false;
				keyHeld = false;
			}

			if (!keyHeld)
			{
				if (menuEvent.type == sf::Event::EventType::KeyPressed
					&& menuEvent.key.code == sf::Keyboard::Space)
				{
					eligibleKeyPressed = true;
					keyHeld = true;
					return selection;
				}
				else if (menuEvent.type == sf::Event::EventType::KeyPressed
					&& menuEvent.key.code == sf::Keyboard::Down)
				{
					MoveDown();
					moveHighlight(window, selection);
				}
				else if ((menuEvent.type == sf::Event::EventType::KeyPressed
					&& menuEvent.key.code == sf::Keyboard::Up))
				{
					MoveUp();
					moveHighlight(window, selection);
				}
				else if (menuEvent.type == sf::Event::Closed)
				{
					eligibleKeyPressed = true;
					keyHeld = true;
					return Close_Window;
				}
			}
		}
	}
}

void PauseMenu::MoveUp()
{
	eligibleKeyPressed = true;
	keyHeld = true;
	selection = static_cast<MenuOptions>(selection - 1);
	if (selection == -1)
		selection = Back_to_Main;
}

void PauseMenu::MoveDown()
{
	eligibleKeyPressed = true;
	keyHeld = true;
	selection = static_cast<MenuOptions>((selection + 1) % (Back_to_Main + 1));
}