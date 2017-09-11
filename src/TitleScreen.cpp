#include "stdafx.h"
#include "TitleScreen.h"

void TitleScreen::Show(sf::RenderWindow& window)
{
	sf::Texture image;
	if (image.loadFromFile("res/img/TitleScreen_Temp.png") != true)
	{
		throw std::invalid_argument("FAILED TO LOAD: TitleScreen");
		return;
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
				return;
			}
		}
	}


}