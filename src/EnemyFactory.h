#pragma once
#include "Enemy.h"

class EnemyFactory
{
public:
	static void SpawnEnemy();

private:
	static void CreateStandard();
	static void CreateScout();
	static void CreateTank();

	static void SelectSpawnPoint(Enemy& createdEnemy);

	static bool firstSpawn;
	static sf::Clock spawnClock;
	static int standardsCreated;
	static int scoutsCreated;
	static int tanksCreated;
};
