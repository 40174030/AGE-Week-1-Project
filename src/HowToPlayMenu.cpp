#include "stdafx.h"
#include "HowToPlayMenu.h"
#include "Game.h"

bool HowToPlayMenu::Show(sf::RenderWindow& window)
{
	sf::Texture image;

	if (image.loadFromFile("res/img/HowToPlay_Temp.png") != true)
	{
		throw std::invalid_argument("FAILED TO LOAD: HowToPlayMenu");
	}

	sf::Sprite sprite(image);

	if (!(Game::FullscreenCheck()))
	{
		sf::Vector2f scale = sprite.getScale();
		sprite.scale(scale.x * Game::downscale, scale.y * Game::downscale);
	}

	window.draw(sprite);
	window.display();

	sf::Event event;

	while (true)
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::KeyPressed
				&& event.key.code == sf::Keyboard::Escape)
			{
				return false;
			}
			else if (event.type == sf::Event::Closed)
				return true;
		}
	}


}