#include "stdafx.h"
#include "MainMenu.h"
#include "Game.h"

MainMenu::MenuOptions MainMenu::Show(sf::RenderWindow& window)
{
	selection = Play_Game;

	// Load menu image from file
	sf::Texture image;

	if (image.loadFromFile("res/img/MainMenu_Temp.png") != true)
	{
		throw std::invalid_argument("FAILED TO LOAD: MainMenu");
		return Quit_Game;
	}
	
	sprite.setTexture(image);

	if (!(Game::fullscreenCheck))
	{
		sf::Vector2f scale = sprite.getScale();
		float downscale = 2.0f / 3.0f;
		sprite.scale(scale.x * downscale, scale.y * downscale);
	}

	window.draw(sprite);

	highlight.setSize(sf::Vector2f(700.0f, 135.0f));
	highlight.setOutlineColor(sf::Color(255, 255, 0));
	highlight.setFillColor(sf::Color::Transparent);
	highlight.setOutlineThickness(10.0f);
	highlight.setPosition(575.0f, 222.0f);

	return GetMenuResponse(window);
}

MainMenu::MenuOptions MainMenu::GetMenuResponse(sf::RenderWindow& window)
{
	sf::Event menuEvent;
	bool keyHeld = false;
	bool eligibleKeyPressed = false;

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
				return Quit_Game;

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
					eligibleKeyPressed = true;
					keyHeld = true;
					selection = static_cast<MenuOptions>((selection + 1) % (Quit_Game + 1));
					moveHighlight(window, selection);
				}
				else if (menuEvent.type == sf::Event::EventType::KeyPressed
					&& menuEvent.key.code == sf::Keyboard::Up)
				{
					eligibleKeyPressed = true;
					keyHeld = true;
					selection = static_cast<MenuOptions>(selection - 1);
					if (selection == -1)
						selection = Quit_Game;
					moveHighlight(window, selection);
				}
				else if (menuEvent.type == sf::Event::Closed)
				{
					eligibleKeyPressed = true;
					keyHeld = true;
					return Quit_Game;
				}
			}
			else if (menuEvent.type == sf::Event::EventType::KeyReleased 
					 && eligibleKeyPressed)
			{
				eligibleKeyPressed = false;
				keyHeld = false;
			}
		}
	}
}

void MainMenu::moveHighlight(sf::RenderWindow& window, MainMenu::MenuOptions newSelection)
{
	switch (newSelection)
	{
	case Play_Game:
	{
		highlight.setPosition(highlightPlayGame);
		break;
	}
	case How_to_Play:
	{
		highlight.setPosition(highlightHowToPlay);
		break;
	}
	case Settings:
	{
		highlight.setPosition(highlightSettings);
		break;
	}
	case Quit_Game:
	{
		highlight.setPosition(highlightQuitGame);
		break;
	}
	}
}