#pragma once

class PlayArea
{
public:
	static void Setup();
	static void Draw(sf::RenderWindow& window, int level);
	static void Reset();
	static int GetLeftmostLane();
	static int GetRightmostLane();

	static sf::RectangleShape lanes[10];

private:
	static int level;
	static int laneLeftmost;
	static int laneRightmost;
};