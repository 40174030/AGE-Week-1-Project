#pragma once
#include "Enemy.h"

class EnemyFactory
{
public:
	static void SpawnEnemy();
	static sf::Clock& GetSpawnClock();
	static void SetFirstSpawn();
	static void SetTimeUntilNextSpawn();

private:
	static void CreateStandard();
	static void CreateScout();
	static void CreateTank();

	static void SelectSpawnPoint(Enemy& createdEnemy);

	static bool firstSpawn;
	static sf::Clock spawnClock;
	const static float respawnTime;
	static float timeUntilNextSpawn;
	static int standardsCreated;
	static int scoutsCreated;
	static int tanksCreated;
};
