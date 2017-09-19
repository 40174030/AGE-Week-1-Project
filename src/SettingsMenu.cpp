#include "stdafx.h"
#include "SettingsMenu.h"
#include "Game.h"

SettingsMenu::MenuOptions SettingsMenu::Show(sf::RenderWindow& window)
{
	selection = Back_to_Main;

	sf::Texture image;

	if (image.loadFromFile("res/img/Settings_Temp.png") != true)
	{
		throw std::invalid_argument("FAILED TO LOAD: SettingsMenu");
	}

	sprite.setTexture(image);

	highlight.setSize(sf::Vector2f(700.0f, 135.0f));
	highlight.setOutlineColor(sf::Color(255, 255, 0));
	highlight.setFillColor(sf::Color::Transparent);
	highlight.setOutlineThickness(10.0f);
	highlight.setPosition(highlightBack);

	window.draw(sprite);

	return GetMenuResponse(window);
}

SettingsMenu::MenuOptions SettingsMenu::GetMenuResponse(sf::RenderWindow& window)
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
				return Back_to_Main;

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
					return Quit_Game;
				}
			}
		}
	}
}

void SettingsMenu::moveHighlight(sf::RenderWindow& window, SettingsMenu::MenuOptions newSelection)
{
	switch (newSelection)
	{
	case Full_HD:
	{
		highlight.setPosition(highlightFullHD);
		break;
	}
	case HD:
	{
		highlight.setPosition(highlightHD);
		break;
	}
	case SD:
	{
		highlight.setPosition(highlightSD);
		break;
	}
	case Back_to_Main:
	{
		highlight.setPosition(highlightBack);
		break;
	}
	}
}

void SettingsMenu::MoveUp()
{
	eligibleKeyPressed = true;
	keyHeld = true;
	selection = static_cast<MenuOptions>(selection - 1);
	if (selection == -1)
		selection = Back_to_Main;
}

void SettingsMenu::MoveDown()
{
	eligibleKeyPressed = true;
	keyHeld = true;
	selection = static_cast<MenuOptions>((selection + 1) % (Back_to_Main + 1));
}