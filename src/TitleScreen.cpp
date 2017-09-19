#include "stdafx.h"
#include "TitleScreen.h"
#include "Game.h"

bool TitleScreen::Show(sf::RenderWindow& window)
{
	sf::Texture image;
	if (image.loadFromFile("res/img/TitleScreen_Temp.png") != true)
	{
		throw std::invalid_argument("FAILED TO LOAD: TitleScreen");
		return true;
	}

	sf::Sprite sprite(image);

	window.draw(sprite);
	window.display();

	sf::Event event;

	while (true)
	{
		while (window.pollEvent(event))
		{
			if (sf::Joystick::isConnected(0))
			{
				if (sf::Joystick::isButtonPressed(0, 7))
					return false;
				else if (sf::Joystick::isButtonPressed(0, 1))
					return true;
			}
			else
			{
			if (event.type == sf::Event::EventType::KeyPressed
				&& event.key.code == sf::Keyboard::Space)
				return false;
			else if (event.type == sf::Event::Closed ||
				(event.type == sf::Event::EventType::KeyPressed
					&& event.key.code == sf::Keyboard::Escape))
				return true;
			}
		}
	}
}