#pragma once
#include "Game_ObjectManager.h"
#include "EnemyFactory.h"
#include "PlayArea.h"
#include "PlayerAvatar.h"

class Game
{
public:
	static void Start();

	//static bool FullscreenCheck();
	static Game_ObjectManager& GetGOM();
	static int GetCurrentLevel();

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

	//enum Resolution
	//{
	//	Full_HD,
	//	HD,
	//	SD
	//};
	
	//static sf::View resolution;
	//static Resolution resOptions;
	//static bool fullscreen;
	static int currentLevel;
	static sf::Clock spawnClock;
	static GameState gameState;
	static sf::RenderWindow mainWindow;
	static Game_ObjectManager game_objectManager;

	//static void ChangeFullscreen();
	//static void ChangeResolution(Resolution selection);

	static void GameLoop();
	static bool IsExiting();

	static void ShowTitleScreen();
	static void ShowMainMenu();
	static void ShowHowToPlay();
	static void ShowSettingsMenu();
	static void ShowPauseMenu();
};