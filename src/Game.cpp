#include "stdafx.h"
#include "Game.h"
#include "TitleScreen.h"
#include "MainMenu.h"
#include "HowToPlayMenu.h"
#include "SettingsMenu.h"
#include "PauseMenu.h"

void Game::Start()
{
	if (gameState != Uninitialized)
		return;

	gameState = Game::ShowingTitle;

	ChangeResolution();

	PlayerAvatar* player = new PlayerAvatar();

	game_objectManager.Add("Player", player);

	while (!IsExiting())
	{
		GameLoop();
	}

	mainWindow.close();
}

bool Game::FullscreenCheck()
{
	return fullscreen;
}

void Game::ChangeResolution()
{
	if (mainWindow.isOpen())
		mainWindow.close();
	if (FullscreenCheck())
	{
		mainWindow.create(sf::VideoMode(
			((int)(screen_Width * (2.0f / 3.0f))), 
			((int)(screen_Height * (2.0f / 3.0f))), 
			32), "As Yet Unnamed");
		fullscreen = false;
	}
	else
	{
		mainWindow.create(sf::VideoMode(
			screen_Width, 
			screen_Height, 
			32), "As Yet Unnamed", 
			sf::Style::Fullscreen);
		fullscreen = true;
	}
	switch (gameState)
	{
	case Game::ShowingTitle:
	{
		break;
	}
	default:
	{
		ShowSettingsMenu();
		break;
	}

	}
}

void Game::ShowTitleScreen()
{
	TitleScreen titleScreen;
	bool quit = titleScreen.Show(mainWindow);
	if (quit)
		gameState = Game::Exiting;
	else
		gameState = Game::ShowingMain;
}

void Game::ShowMainMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuOptions result = mainMenu.Show(mainWindow);
	game_objectManager.GetClock().restart();

	switch (result)
	{
	case MainMenu::Play_Game:
	{
		gameState = Game::Playing;
		break;
	}
	case MainMenu::How_to_Play:
	{
		gameState = Game::ShowingHowTo;
		break;
	}
	case MainMenu::Settings:
	{
		gameState = Game::ShowingSettings;
		break;
	}
	case MainMenu::Quit_Game:
	{
		gameState = Game::Exiting;
		break;
	}
	}
}

void Game::ShowHowToPlay()
{
	HowToPlayMenu htpMenu;
	bool quit = htpMenu.Show(mainWindow);
	if (quit)
		gameState = Game::Exiting;
	else
		gameState = Game::ShowingMain;
}

void Game::ShowSettingsMenu()
{
	SettingsMenu settings;
	bool quit = settings.Show(mainWindow);
	if (quit)
		gameState = Game::Exiting;
	else
		gameState = Game::ShowingMain;
}

void Game::ShowPauseMenu()
{
	PauseMenu pauseMenu;
	PauseMenu::MenuOptions result = pauseMenu.Show(mainWindow);

	switch (result)
	{
	case PauseMenu::Resume_Game:
	{
		gameState = Game::Playing;
		break;
	}
	case PauseMenu::Back_to_Main:
	{
		gameState = Game::ShowingMain;
		break;
	}
	case PauseMenu::Close_Window:
	{
		gameState = Game::Exiting;
		break;
	}
	}
}

bool Game::IsExiting()
{
	if (gameState == Game::Exiting)
		return true;
	else
		return false;
}


void Game::GameLoop()
{
	sf::Event currentEvent;
	mainWindow.pollEvent(currentEvent);

	switch (gameState)
	{
	case Game::ShowingTitle:
	{
		ShowTitleScreen();
		break;
	}
	case Game::ShowingMain:
	{
		ShowMainMenu();
		game_objectManager.ResetAll();
		break;
	}
	case Game::Playing:
	{
		mainWindow.clear();

		PlayArea playArea;
		playArea.Setup();
		playArea.Draw(mainWindow, 1);
		game_objectManager.UpdateAll();
		game_objectManager.DrawAll(mainWindow);

		mainWindow.display();

		if (currentEvent.type == sf::Event::Closed)
			gameState = Game::Exiting;
		if (currentEvent.type == sf::Event::KeyPressed)
		{
			if (currentEvent.key.code == sf::Keyboard::Escape)
				gameState = Game::Paused;
		}
		break;
	}
	case Game::ShowingHowTo:
	{
		ShowHowToPlay();
		break;
	}
	case Game::ShowingSettings:
	{
		ShowSettingsMenu();
		break;
	}
	case Game::Paused:
	{
		ShowPauseMenu();
		break;
	}
	}
}

bool Game::fullscreen = false;
const float Game::downscale = 2.0f / 3.0f;
Game::GameState Game::gameState = Uninitialized;
sf::RenderWindow Game::mainWindow;
Game_ObjectManager Game::game_objectManager;