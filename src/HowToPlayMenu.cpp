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

	if (!(Game::fullscreenCheck))
	{
		sf::Vector2f scale = sprite.getScale();
		float downscale = 2.0f / 3.0f;
		sprite.scale(scale.x * downscale, scale.y * downscale);
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