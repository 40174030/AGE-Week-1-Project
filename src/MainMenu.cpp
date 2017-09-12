#include "stdafx.h"
#include "MainMenu.h"

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
	window.draw(sprite);

	highlight.setSize(sf::Vector2f(700.0f, 135.0f));
	highlight.setOutlineColor(sf::Color(255, 255, 0));
	highlight.setFillColor(sf::Color::Transparent);
	highlight.setOutlineThickness(10.0f);
	highlight.setPosition(575.0f, 222.0f);
	window.draw(highlight);
	window.display();

	return GetMenuResponse(window);
}

MainMenu::MenuOptions MainMenu::GetMenuResponse(sf::RenderWindow& window)
{
	sf::Event menuEvent;
	bool keyHeld = false;
	bool eligibleKeyPressed = false;

	while (true)
	{

		while (window.pollEvent(menuEvent))
		{
			switch (selection)
			{
			case (Play_Game):
			{
				highlight.setPosition(highlightPlayGame);
			}
			case (How_to_Play):
			{
				highlight.setPosition(highlightHowToPlay);
			}
			case (Settings):
			{
				highlight.setPosition(highlightSettings);
			}
			case (Quit_Game):
			{
				highlight.setPosition(highlightQuitGame);
			}
			}

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
				}
				else if (menuEvent.type == sf::Event::EventType::KeyPressed
					&& menuEvent.key.code == sf::Keyboard::Up)
				{
					eligibleKeyPressed = true;
					keyHeld = true;
					selection = static_cast<MenuOptions>(selection - 1);
					if (selection == -1)
						selection = Quit_Game;
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