#pragma once
#include "Game_ObjectManager.h"

class Game
{
public:
	static void Start();

	const static int screen_Width = 1920;
	const static int screen_Height = 1080;

private:
	static void GameLoop();
	static bool IsExiting();
	static void ShowTitleScreen();
	static void ShowMainMenu();
	static void ShowPauseMenu();
	
	enum GameState
	{
		Uninitialized,
		ShowingTitle,
		ShowingMenu,
		Playing,
		Paused,
		Exiting
	};

	static GameState gameState;
	static sf::RenderWindow mainWindow;
	static Game_ObjectManager game_objectManager;
};