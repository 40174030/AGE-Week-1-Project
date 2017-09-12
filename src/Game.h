#pragma once
#include "Game_ObjectManager.h"
#include "PlayerShip.h"

class Game
{
public:
	static void Start();

	static bool fullscreenCheck();

	const static int screen_Width = 1920;
	const static int screen_Height = 1080;

private:
	enum GameState
	{
		Uninitialized,
		ShowingTitle,
		ShowingMain,
		ShowingHowTo,
		ShowingSettings,
		Playing,
		Paused,
		Exiting
	};
	
	static bool fullscreen;
	static GameState gameState;
	static sf::RenderWindow mainWindow;
	static Game_ObjectManager game_objectManager;

	static void ChangeResolution();
	static void GameLoop();
	static bool IsExiting();
	static void ShowTitleScreen();
	static void ShowMainMenu();
	static void ShowHowToPlay();
	static void ShowSettingsMenu();
	static void ShowPauseMenu();
};