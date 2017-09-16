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

	//if (Game::FullscreenCheck())
	//{
	//	incrementX = Game::fullscreen_Width / (sizeof(lanes) / sizeof(*lanes));
	//	screenHeight = (float)Game::fullscreen_Height;
	//}
	//else
	//{
	//	incrementX = (Game::windowed_Width / (sizeof(lanes) / sizeof(*lanes)));
	//	screenHeight = (float)Game::windowed_Height;
	//}

	for (int x = 0; x < (sizeof(lanes) / sizeof(*lanes)); x++)
	{
		sf::RectangleShape lane = sf::RectangleShape(sf::Vector2f(incrementX, screenHeight));
		lane.setPosition(initialX, 0.0f);
		lanes[x] = lane;
		initialX += incrementX;
	}
}

void PlayArea::Draw(sf::RenderWindow& window, int level)
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

void PlayArea::Reset()
{

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
int PlayArea::level;
int PlayArea::laneLeftmost;
int PlayArea::laneRightmost;
