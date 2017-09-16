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

	ChangeResolution(resOptions);
	ChangeFullscreen();

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

Game_ObjectManager& Game::GetGOM()
{
	return Game::game_objectManager;
}

void Game::ChangeFullscreen()
{
	if (mainWindow.isOpen())
		mainWindow.close();

	if (FullscreenCheck())
	{
		mainWindow.create(sf::VideoMode(
			mainWindow.getSize().x, 
			mainWindow.getSize().y, 
			32), "Cutting Corners");
		fullscreen = false;
	}
	else
	{
		mainWindow.create(sf::VideoMode(
			mainWindow.getSize().x,
			mainWindow.getSize().y,
			32), "Cutting Corners", 
			sf::Style::Fullscreen);
		fullscreen = true;
	}

	mainWindow.setView(sf::View(sf::FloatRect(0.0f, 0.0f, screen_Width, screen_Height)));

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

void Game::ChangeResolution(Resolution resSelection)
{
	sf::Vector2u full_hd = sf::Vector2u(screen_Width, screen_Height);
	sf::Vector2u hd = sf::Vector2u(1280, 720);
	sf::Vector2u sd = sf::Vector2u(720, 480);

	switch (resSelection)
	{
	case Full_HD:
	{
		mainWindow.setSize(full_hd);
		break;
	}
	case HD:
	{
		mainWindow.setSize(hd);
		break;
	}
	case SD:
	{
		mainWindow.setSize(sd);
		break;
	}
	}

	mainWindow.setView(sf::View(sf::FloatRect(0.0f, 0.0f, screen_Width, screen_Height)));
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

		PlayArea::Setup();
		PlayArea::Draw(mainWindow, currentLevel);
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

sf::View Game::resolution;
bool Game::fullscreen = false;
int Game::currentLevel = 1;
Game::GameState Game::gameState = Uninitialized;
Game::Resolution Game::resOptions = Full_HD;
sf::RenderWindow Game::mainWindow;
Game_ObjectManager Game::game_objectManager;