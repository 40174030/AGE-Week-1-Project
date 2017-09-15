#pragma once
#include "Game_ObjectManager.h"
#include "PlayArea.h"
#include "PlayerAvatar.h"

class Game
{
public:
	static void Start();

	static bool FullscreenCheck();

	const static int fullscreen_Width = 1920;
	const static int fullscreen_Height = 1080;

	const static int windowed_Width = 1280;
	const static int windowed_Height = 720;

	const static float downscale;

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
	static int currentLevel;
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