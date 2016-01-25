#pragma once
#include "..\System\AssetManager.h"
#include "..\System\Input.h"
#include "..\System\SceneManager.h"
#include "..\Entity\stdEntity.h"
#include "..\Core\STDUNC.h"
#include "..\Libs\BuitInShaders.h"

enum EnemyType
{
	miniPather,
	regularShooter,
	megaCharger,
	asterioid,
	electric,
	swerver
};

struct SupaLaser
{
	float timeAlive;
	float lifeTime;
	stdEntity* ent;
};

struct EnemyPath
{
	vec2 leftBoundary;
	vec2 rightBoundary;
	float middleSlope;
	float middleOffset;
};

struct dfEnemy;

struct dfEnemyElectric
{
	dfEnemy* linkedEnemy;
	bool leader;
};

struct dfEnemySwerve
{
	float veloc;
	float swrvAmnt;
	float swrvSpd;
	float startingHeight;
};

struct dfEnemyCharge
{
	float timer;
	bool doneMoving;
	bool doneFiring;
};

const float ENEMY_MAX_SHAKE = 0.3;

struct dfEnemy
{
	EnemyType type;
	EnemyPath path;
	stdEntity* entity;
	float spd;
	int health;
	
	dfEnemySwerve swerve;
	dfEnemyCharge charge;
	dfEnemyElectric elec;

	Rect renderRect;

	float shakeTime;
	float flashTime;
};

void InitLevel1Scene();

void DufradiuInitGame();
void DufradiusUpdate();

// ship vars
const float shipSpd = 500.f;
//ship funcs
void MoveShip(int shipNum);
void ShootShip(int shipNum);
void PlayerDie();

// world objects
const float bulletSpd = 750.f;
void ProcessBullets();

//enemies
void BasicEnemyInit(dfEnemy* e);
void UpdateEnemies();
void SetupMiniPather(float lHeight, float rHeight);
void SetupSwerver(float height, float swrvAmnt);
void SetupMegaCharger(float height, float waitTime);
void SetupElectric(float height, float offsetX, float offsetY);

void UpdateLasers();

void ChargerFire(dfEnemy e);