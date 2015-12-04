#pragma once
#include "dfcomponent.h"
#include "STDUNC.h"

struct ParticleInfo
{
	vec2 pos;
	float w;
	float h;
	float rotation;
	vec4 color;
	vec2 veloc;
	float acc;
	float lifetime;
	float lifespan;
	bool dead;
};

class dfParticleSystem :
	public dfComponent
{
public:
	dfParticleSystem(void);
	virtual ~dfParticleSystem(void);
	virtual void Init();
	virtual void Update();

	void InitParticle(ParticleInfo &p);
	void CreatParticle();
	void UpdateParticle(ParticleInfo &particle);

	const MAX_PARTICLES = 8192;
	int numParticles;
	ParticleInfo particles[MAX_PARTICLES];
};

