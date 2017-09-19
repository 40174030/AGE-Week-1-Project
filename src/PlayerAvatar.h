#pragma once
#include "Game_Object.h"

class PlayerAvatar : public Game_Object
{
public:
	PlayerAvatar();
	~PlayerAvatar();

	void Update(float elapsedTime);
	void Draw(sf::RenderWindow& window);
	void Reset();

	float& GetHealth();
	bool IsRecoveryActive();
	bool IsSloMoActive();
	bool IsSuperFireActive();
	void DeactivateRecovery();
	void DeactivateSloMo();
	void DeactivateSuperFire();
	void ResetSHA();

private:
	void MoveLeft();
	void MoveRight();
	void FireWeapon();
	
	bool stillHoldingA;
	sf::Clock fireClock;
	float health;
	float velocity;
	int projectilesFired;
	float sinceLastFire;
	float fireRate_Current;
	bool active_Recovery;
	bool active_SloMo;
	bool active_SuperFire;
	const float fireRate_Original = 0.2f;
	const float max_velocity = 1000.0f;
};