#include "stdafx.h"
#include "EnemyFactory.h"
#include "PlayArea.h"
#include "Game.h"

void EnemyFactory::SpawnEnemy()
{
	if (firstSpawn)
	{
		firstSpawn = false;
		spawnClock.restart();
	}
	else if (spawnClock.getElapsedTime().asSeconds() < 1.5f)
		return;
	else
	{
		srand(time(NULL));
		int random = std::rand() % Game::GetCurrentLevel();
		switch (random)
		{
		case STANDARD: { CreateStandard(); break; }
		case SCOUT: { CreateScout(); break; }
		case TANK: { CreateTank(); break; }
		}
		spawnClock.restart();
	}
}

void EnemyFactory::CreateStandard()
{
	Enemy* standard = new Enemy(STANDARD);
	standardsCreated++;
	Game::GetGOM().Add("Enemy_Standard" + std::to_string(standardsCreated), standard);
	EnemyFactory::SelectSpawnPoint(*standard);
}

void EnemyFactory::CreateScout()
{
	Enemy* scout = new Enemy(SCOUT);
	scoutsCreated++;
	Game::GetGOM().Add("Enemy_Scout" + std::to_string(scoutsCreated), scout);
	EnemyFactory::SelectSpawnPoint(*scout);
}

void EnemyFactory::CreateTank()
{
	Enemy* tank = new Enemy(TANK);
	tanksCreated++;
	Game::GetGOM().Add("Enemy_Tank" + std::to_string(tanksCreated), tank);
	EnemyFactory::SelectSpawnPoint(*tank);
}

void EnemyFactory::SelectSpawnPoint(Enemy& createdEnemy)
{
	int random = std::rand() % 
				 (PlayArea::GetRightmostLane() - PlayArea::GetLeftmostLane()) 
				 + PlayArea::GetLeftmostLane();
	createdEnemy.SetPosition(PlayArea::lanes[random].getPosition().x + 
							(PlayArea::lanes[random].getGlobalBounds().width / 2), 0.0f);
}

int EnemyFactory::standardsCreated = 0;
int EnemyFactory::scoutsCreated = 0;
int EnemyFactory::tanksCreated = 0;
bool EnemyFactory::firstSpawn = true;
sf::Clock EnemyFactory::spawnClock;
