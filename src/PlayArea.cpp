#include "stdafx.h"
#include "PlayArea.h"
#include "Game.h"

void PlayArea::Setup()
{
	float initialX = 0.0f;
	float incrementX;

	float screenHeight;

	incrementX = (Game::screen_Width / (sizeof(lanes) / sizeof(*lanes)));
	screenHeight = (float)Game::screen_Height;

	for (int x = 0; x < (sizeof(lanes) / sizeof(*lanes)); x++)
	{
		sf::RectangleShape lane = sf::RectangleShape(sf::Vector2f(incrementX, screenHeight));
		lane.setPosition(initialX, 0.0f);
		lanes[x] = lane;
		initialX += incrementX;
	}

	HUD = sf::RectangleShape(sf::Vector2f(Game::screen_Width, 100.0f));
	HUD.setPosition(0.0f, 980.0f);
	HUD.setFillColor(sf::Color(0, 0, 0));
}

void PlayArea::DrawEnvironment(sf::RenderWindow& window, int level)
{
	switch (level)
	{
	case 1: { laneLeftmost = 3; laneRightmost = 6; break; }
	case 2: { laneLeftmost = 2; laneRightmost = 7; break; }
	case 3: { laneLeftmost = 1; laneRightmost = 8; break; }
	case 4: { laneLeftmost = 0; laneRightmost = 9; break; }
	}

	for (int x = 0; x < (sizeof(lanes) / sizeof(*lanes)); x++)
	{
		if (x < laneLeftmost || x > laneRightmost)
			lanes[x].setFillColor(sf::Color(0, 0, 0));
		else
			lanes[x].setFillColor(sf::Color(255, 255, 0));
		window.draw(lanes[x]);
	}
}

void PlayArea::DrawHUD(sf::RenderWindow& window, int yourScore, int highScore, float yourHealth)
{
	sf::Font font1;
	font1.loadFromFile("res/Organo.ttf");
	
	sf::Text title_YourScore("Score:\t" + std::to_string(yourScore), font1);
	sf::Text title_HighScore("Hi-Score:\t" + std::to_string(highScore), font1);
	sf::Text title_YourHealth("Health: " + std::to_string((int)yourHealth), font1);
	sf::Text title_Recovery("Recovering health!", font1);
	sf::Text title_SloMoActive("Slo-mo activated!", font1);
	sf::Text title_FireRateIncrease("Fire rate increased!", font1);

	title_YourScore.setCharacterSize(30);
	title_YourScore.setStyle(sf::Text::Bold);
	title_YourScore.setColor(sf::Color(255, 255, 0));
	title_YourScore.setPosition(HUD.getPosition() + sf::Vector2f(30.0f, 10.0f));

	title_HighScore.setCharacterSize(30);
	title_HighScore.setStyle(sf::Text::Bold);
	title_HighScore.setColor(sf::Color(255, 255, 0));
	title_HighScore.setPosition(title_YourScore.getPosition() + sf::Vector2f(0.0f, 40.0f));

	title_YourHealth.setCharacterSize(30);
	title_YourHealth.setStyle(sf::Text::Bold);
	title_YourHealth.setColor(sf::Color(255, 255, 0));
	title_YourHealth.setPosition(HUD.getPosition() + sf::Vector2f((Game::screen_Width / 2) - 110.0f, (HUD.getGlobalBounds().height / 2) - 30.0f));

	title_Recovery.setCharacterSize(20);
	title_Recovery.setStyle(sf::Text::Bold);
	title_Recovery.setColor(sf::Color(255, 255, 0));
	title_Recovery.setPosition(sf::Vector2f(Game::screen_Width - 300, HUD.getGlobalBounds().top + 10.0f));

	title_SloMoActive.setCharacterSize(20);
	title_SloMoActive.setStyle(sf::Text::Bold);
	title_SloMoActive.setColor(sf::Color(255, 255, 0));
	title_SloMoActive.setPosition(title_Recovery.getPosition() + sf::Vector2f(0.0f, 25.0f));

	title_FireRateIncrease.setCharacterSize(20);
	title_FireRateIncrease.setStyle(sf::Text::Bold);
	title_FireRateIncrease.setColor(sf::Color(255, 255, 0));
	title_FireRateIncrease.setPosition(title_SloMoActive.getPosition() + sf::Vector2f(0.0f, 25.0f));

	PlayerAvatar* player = Game::ReturnPlayer();

	window.draw(HUD);
	window.draw(title_YourScore);
	window.draw(title_HighScore);
	window.draw(title_YourHealth);
	if (player->IsRecoveryActive())
		window.draw(title_Recovery);
	if (player->IsSloMoActive())
		window.draw(title_SloMoActive);
	if (player->IsSuperFireActive())
		window.draw(title_FireRateIncrease);
}

int PlayArea::GetLeftmostLane()
{
	return laneLeftmost;
}

int PlayArea::GetRightmostLane()
{
	return laneRightmost;
}

sf::RectangleShape PlayArea::lanes[10];
sf::RectangleShape PlayArea::HUD;
int PlayArea::laneLeftmost;
int PlayArea::laneRightmost;
