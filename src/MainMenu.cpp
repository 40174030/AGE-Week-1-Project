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

	highlight.setSize(sf::Vector2f(700.0f, 135.0f));
	highlight.setOutlineColor(sf::Color(255, 255, 0));
	highlight.setFillColor(sf::Color::Transparent);
	highlight.setOutlineThickness(10.0f);
	highlight.setPosition(highlightPlayGame);

	if (!(Game::FullscreenCheck()))
	{
		sf::Vector2f scale = sprite.getScale();
		sf::Vector2f originalSize = highlight.getSize();
		
		sprite.scale(scale * Game::downscale);
		highlight.setSize(sf::Vector2f(originalSize * Game::downscale));
		highlight.setPosition(sf::Vector2f(highlightPlayGame * Game::downscale));
		highlight.setOutlineThickness(6.7f);
	}

	window.draw(sprite);

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
		if (Game::FullscreenCheck())
			highlight.setPosition(highlightPlayGame);
		else
			highlight.setPosition(sf::Vector2f(highlightPlayGame * Game::downscale));
		break;
	}
	case How_to_Play:
	{
		if (Game::FullscreenCheck())
			highlight.setPosition(highlightHowToPlay);
		else
			highlight.setPosition(sf::Vector2f(highlightHowToPlay * Game::downscale));
		break;
	}
	case Settings:
	{
		if (Game::FullscreenCheck())
			highlight.setPosition(highlightSettings);
		else
			highlight.setPosition(sf::Vector2f(highlightSettings * Game::downscale));
		break;
	}
	case Quit_Game:
	{
		if (Game::FullscreenCheck())
			highlight.setPosition(highlightQuitGame);
		else
			highlight.setPosition(sf::Vector2f(highlightQuitGame * Game::downscale));
		break;
	}
	}
}