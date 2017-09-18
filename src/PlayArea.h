#pragma once

class PlayArea
{
public:
	static void Setup();
	static void DrawEnvironment(sf::RenderWindow& window, int level);
	static void DrawHUD(sf::RenderWindow& window);
	static int GetLeftmostLane();
	static int GetRightmostLane();

	static sf::RectangleShape lanes[10];
	static sf::RectangleShape HUD;

private:
	static int level;
	static int laneLeftmost;
	static int laneRightmost;
};