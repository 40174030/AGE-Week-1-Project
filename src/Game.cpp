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

	windowView = sf::View(sf::FloatRect(0.0f, 0.0f, screen_Width, screen_Height));
	mainWindow.setView(windowView);

	PlayArea::Setup();
	PlayerAvatar* player = new PlayerAvatar();

	game_objectManager.Add("Player", player);

	while (!IsExiting())
	{
		GameLoop();
	}

	mainWindow.close();
}


Game_ObjectManager& Game::GetGOM()
{
	return Game::game_objectManager;
}


int Game::GetCurrentLevel()
{
	return currentLevel;
}


void Game::ChangeResolution(Resolution resSelection)
{
	sf::Vector2u full_hd = sf::Vector2u(screen_Width, screen_Height);
	sf::Vector2u hd = sf::Vector2u(1280, 720);
	sf::Vector2u sd = sf::Vector2u(640, 480);

	if (mainWindow.isOpen())
		mainWindow.close();

	switch (resSelection)
	{
	case Full_HD:
	{
		mainWindow.create(sf::VideoMode(
			full_hd.x,
			full_hd.y,
			32), "Cutting Corners",
			sf::Style::Fullscreen);
		break;
	}
	case HD:
	{
		mainWindow.create(sf::VideoMode(
			hd.x,
			hd.y,
			32), "Cutting Corners");
		mainWindow.setView(windowView);
		break;
	}
	case SD:
	{
		mainWindow.create(sf::VideoMode(
			sd.x,
			sd.y,
			32), "Cutting Corners");
		mainWindow.setView(windowView);
		break;
	}
	}

	mainWindow.setView(windowView);
}


void Game::ShowTitleScreen()
{
	TitleScreen titleScreen;
	bool quit = titleScreen.Show(mainWindow);
	if (quit)
		gameState = Game::Exiting;
	else
		gameState = Game::ShowingMain;
	ResetAllClocks();
}


void Game::ShowMainMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuOptions result = mainMenu.Show(mainWindow);

	currentLevel = 1;
	timeUntilNextLevel = levelDuration;
	EnemyFactory::SetFirstSpawn();
	ResetAllClocks();

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
	ResetAllClocks();
}


void Game::ShowSettingsMenu()
{
	SettingsMenu settings;
	bool quit = settings.Show(mainWindow);
	if (quit)
		gameState = Game::Exiting;
	else
		gameState = Game::ShowingMain;
	ResetAllClocks();
}


void Game::ShowPauseMenu()
{
	PauseMenu pauseMenu;
	PauseMenu::MenuOptions result = pauseMenu.Show(mainWindow);

	ResetAllClocks();

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


int& Game::GetYourScore()
{
	return yourScore;
}


int& Game::GetHighScore()
{
	return highScore;
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
	PlayerAvatar* player = ReturnPlayer();
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
		game_objectManager.ResetAll();
		yourScore = 0;
		ShowMainMenu();
		EnemyFactory::SetFirstSpawn();
		EnemyFactory::SetTimeUntilNextSpawn();
		break;
	}
	case Game::Playing:
	{
		mainWindow.clear();

		if (timeUntilNextLevel <= 0.0f && currentLevel < 4)
		{
			currentLevel++;
			timeUntilNextLevel = levelDuration;
		}
		else
			timeUntilNextLevel -= frameTime.getElapsedTime().asSeconds();

		frameTime.restart();

		PlayArea::DrawEnvironment(mainWindow, currentLevel);
		EnemyFactory::SpawnEnemy();
		game_objectManager.UpdateAll();
		game_objectManager.DrawAll(mainWindow);

		if (GetYourScore() > GetHighScore())
			highScore = yourScore;

		PlayerAvatar* player = ReturnPlayer();
		if (player->GetHealth() <= 0.0f)
			gameState = Game::ShowingMain;

		PlayArea::DrawHUD(mainWindow, GetYourScore(), GetHighScore(), player->GetHealth());

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


void Game::ResetAllClocks()
{
	game_objectManager.GetClock().restart();
	EnemyFactory::GetSpawnClock().restart();
	frameTime.restart();
}

PlayerAvatar* Game::ReturnPlayer()
{
	std::map<std::string, Game_Object*>::iterator itr = Game::GetGOM().GetAllObjects().find("Player");
	PlayerAvatar* player = static_cast<PlayerAvatar*>(Game::GetGOM().GetSingleObject(itr->first));
	return player;
}


Game::Resolution Game::resOptions = HD;
int Game::currentLevel = 1;
sf::Clock Game::frameTime;
const float Game::levelDuration = 20.0f;
float Game::timeUntilNextLevel = Game::levelDuration; 
int Game::yourScore;
int Game::highScore = 0;
Game::GameState Game::gameState = Uninitialized;
sf::RenderWindow Game::mainWindow;
sf::View Game::windowView;
Game_ObjectManager Game::game_objectManager;
