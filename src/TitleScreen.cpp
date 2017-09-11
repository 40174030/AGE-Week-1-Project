#include "stdafx.h"
#include "Game.h"
#include "TitleScreen.h"

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
			if (event.type == sf::Event::EventType::KeyPressed
				&& event.key.code == sf::Keyboard::Space)
			{
				return false;
			}
			else if (event.type == sf::Event::Closed)
				return true;
		}
	}


}