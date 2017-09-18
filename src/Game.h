#pragma once
#include "Game_ObjectManager.h"
#include "EnemyFactory.h"
#include "PlayArea.h"
#include "PlayerAvatar.h"

class Game
{
public:
	static void Start();

	static Game_ObjectManager& GetGOM();
	static int GetCurrentLevel();
	static int& GetYourScore();
	static int& GetHighScore();
	static PlayerAvatar* ReturnPlayer();

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
		ShowingScores,
		Playing,
		Paused,
		Exiting
	};

	enum Resolution
	{
		Full_HD,
		HD,
		SD
	};
	
	static Resolution resOptions;
	static bool paused;
	static int currentLevel;
	static sf::Clock spawnClock;
	static sf::Clock frameTime;
	const static float levelDuration;
	static float timeUntilNextLevel;
	static int yourScore;
	static int highScore;
	static GameState gameState;
	static sf::RenderWindow mainWindow;
	static sf::View windowView;
	static Game_ObjectManager game_objectManager;

	static void ChangeResolution(Resolution selection);
	static void GameLoop();
	static bool IsExiting();
	static void ResetAllClocks();
	static void ShowTitleScreen();
	static void ShowMainMenu();
	static void ShowHowToPlay();
	static void ShowSettingsMenu();
	static void ShowPauseMenu();
};