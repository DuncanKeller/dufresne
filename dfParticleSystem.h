#pragma once
#include "dfcomponent.h"
#include "STDUNC.h"
#include "dfBasic.h"
#include "Mesh.h"
#include "Renderer.h"

class dfParticleSystem :
	public dfComponent
{
public:
	dfParticleSystem(void);
	virtual ~dfParticleSystem(void);
	virtual void Init();
	virtual void Update();

	void InitParticle(ParticleInfo &p);
	void CreateParticle();
	void UpdateParticle(ParticleInfo &particle);

	// BLOCK - particle params used when spawing a particle
	bool useSpawnRect; // as opposed to spawn point
	Rect spawnRect;
	vec2 spawnPoint;
	float minVeloc;
	float maxVeloc;
	float minLifespan;
	float maxLifespan;
	float minAcc;
	float maxAcc;
	vec4 startColor;
	vec4 endColor;
	float beginFadeTime; // zero to one
	float minStartRotation;
	float maxStartRotation;
	float minRotationSpd;
	float maxRotationSpd;
	float minParticleSize;
	float maxParticleSize;
	bool fadeSize;
	std::vector<unsigned int> textures;

	// params related to spawn timing
	bool active;
	float timer;
	float nextParticleTime;
	float minSecondsBetweenParticles;
	float maxSecondsBetweenParticles;

	int layer;
	ParticleBox pbox;
	Renderer* renderer;
};

