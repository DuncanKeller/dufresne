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
	void UpdateParticle(ParticleInfo &particle, int index);

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
	std::vector<vec4> startColors;
	vec4 endColor;
	float beginFadeTime; // zero to one
	float minStartRotation;
	float maxStartRotation;
	float minRotationSpd;
	float maxRotationSpd;
	float minParticleSize;
	float maxParticleSize;
	bool fadeSize;
	std::vector<TextureInfo> textures;

	// params related to spawn timing
	int layer;
	bool active;
	int maxActiveParticles;
	float minSecondsBetweenParticles;
	float maxSecondsBetweenParticles;

	float timer;
	float nextParticleTime;

	Renderer* parentRenderer;
	Renderer particleRenderers[MAX_PARTICLES];
	int currentParticleCap; // used to determine how far to iterate over particles

private:
	int numParticles;
	ParticleInfo particles[MAX_PARTICLES];
};

