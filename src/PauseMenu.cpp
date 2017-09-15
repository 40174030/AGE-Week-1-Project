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

	//if (!(Game::FullscreenCheck()))
	//{
	//	sf::Vector2f scale = sprite.getScale();
	//	sf::Vector2f originalSize = highlight.getSize(); 
	//	
	//	sprite.scale(scale * Game::downscale);
	//	highlight.setSize(sf::Vector2f(originalSize * Game::downscale));
	//	highlight.setPosition(sf::Vector2f(highlightResume * Game::downscale));
	//	highlight.setOutlineThickness(6.7f);
	//}

	window.draw(sprite);

	return GetMenuResponse(window);
}


void PauseMenu::moveHighlight(sf::RenderWindow& window, PauseMenu::MenuOptions newSelection)
{
	switch (newSelection)
	{
	case Resume_Game:
	{
		//if (Game::FullscreenCheck())
			highlight.setPosition(highlightResume);
		//else
		//	highlight.setPosition(sf::Vector2f(highlightResume* Game::downscale));
		break;
	}
	case Back_to_Main:
	{
		//if (Game::FullscreenCheck())
			highlight.setPosition(highlightBackTo);
		//else
		//	highlight.setPosition(sf::Vector2f(highlightBackTo * Game::downscale));
		break;
	}
	}
}

PauseMenu::MenuOptions PauseMenu::GetMenuResponse(sf::RenderWindow& window)
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
					selection = static_cast<MenuOptions>((selection + 1) % (Back_to_Main + 1));
					moveHighlight(window, selection);
				}
				else if (menuEvent.type == sf::Event::EventType::KeyPressed
					&& menuEvent.key.code == sf::Keyboard::Up)
				{
					eligibleKeyPressed = true;
					keyHeld = true;
					selection = static_cast<MenuOptions>(selection - 1);
					if (selection == -1)
						selection = Back_to_Main;
					moveHighlight(window, selection);
				}
				else if (menuEvent.type == sf::Event::Closed)
				{
					eligibleKeyPressed = true;
					keyHeld = true;
					return Close_Window;
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