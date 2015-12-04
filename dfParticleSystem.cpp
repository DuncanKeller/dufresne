#include "dfParticleSystem.h"


dfParticleSystem::dfParticleSystem(void)
{
}


dfParticleSystem::~dfParticleSystem(void)
{
}

void dfParticleSystem::Init()
{
	dfComponent::Init();
}

void dfParticleSystem::Update()
{
	dfComponent::Init();

	for(int i = 0; i < numParticles; i++)
	{
		if(!particles[i].dead)
		{
			UpdateParticle(particles[i]);
		}
	}
}

void InitParticle(ParticleInfo &p)
{
	p.acc = 0;
	p.color = vec4(0.f, 0.f, 0.f, 0.f);
	p.dead = false;
	p.h = 0;
	p.lifespan = 0.f;
	p.lifetime = 0.f;
	p.rotation = 0.f;
	p.veloc = vec2(0.f, 0.f);
	p.w = 0;
	p.pos = vec2(0.f, 0.f);
}

void dfParticleSystem::CreatParticle()
{
	ParticleInfo p;
	InitParticle(p);

	numParticles++;

	for(int i = 0; i < MAX_PARTICLES; i++)
	{
		if(particles[i].dead)
		{
			particles[i] = p;
			return;
		}
	}

	dfLog("Could not create particle. Max particles!"); // todo dfwarn
}

void dfParticleSystem::UpdateParticle(ParticleInfo &particle)
{
	particle.lifetime += 0.05f; // todo dt
	if(particle.lifetime > particle.lifespan)
	{
		particle.dead = true;
		return;
	}


}