#include "stdafx.h"
#include "Game.h"
#include "TitleScreen.h"
#include "MainMenu.h"

void Game::Start()
{
	if (gameState != Uninitialized)
		return;

	mainWindow.create(sf::VideoMode(screen_Width, screen_Height, 32), 
					  "As Yet Unnamed", sf::Style::Fullscreen);
	gameState = Game::ShowingTitle;

	while (!IsExiting())
	{
		GameLoop();
	}

	mainWindow.close();
}

void Game::ShowTitleScreen()
{
	TitleScreen titleScreen;
	bool quit = titleScreen.Show(mainWindow);
	if (quit)
		gameState = Game::Exiting;
	else
		gameState = Game::ShowingMenu;
}

void Game::ShowMainMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(mainWindow);
	game_objectManager.GetClock().restart();

	switch (result)
	{
	case MainMenu::Exit:
	{
		gameState = Game::Exiting;
		break;
	}
	case MainMenu::Play:
	{
		gameState = Game::Playing;
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
	case Game::ShowingMenu:
	{
		ShowMainMenu();
		game_objectManager.ResetAll();
		break;
	}
	case Game::Playing:
	{
		mainWindow.clear(sf::Color(255, 0, 0));
		game_objectManager.UpdateAll();
		game_objectManager.DrawAll(mainWindow);
		mainWindow.display();

		if (currentEvent.type == sf::Event::Closed)
			gameState = Game::Exiting;
		if (currentEvent.type == sf::Event::KeyPressed)
		{
			if (currentEvent.key.code == sf::Keyboard::Escape)
				gameState = Game::ShowingMenu;
		}
		break;
	}
	}
}

Game::GameState Game::gameState = Uninitialized;
sf::RenderWindow Game::mainWindow;
Game_ObjectManager Game::game_objectManager;