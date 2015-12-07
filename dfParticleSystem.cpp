#include "dfParticleSystem.h"
#include "Entity.h"

// todo move in stdunc or something
float randf()
{
	return (rand() % 100) / 100.f;
}

dfParticleSystem::dfParticleSystem(void)
{
	useSpawnRect = false;
	spawnRect = Rect();
	spawnPoint = vec2(0.f,0.f);
	minVeloc = 0.f;
	maxVeloc = 0.f;
	minLifespan = 0.f;
	maxLifespan = 0.f;
	minAcc = 0.f;
	maxAcc = 0.f;
	startColor = vec4(1.f, 1.f, 1.f, 1.f);
	endColor = vec4(1.f, 1.f, 1.f, 1.f);
	minStartRotation = 0.f;
	maxStartRotation = 0.f;
	minRotationSpd = 0.f;
	maxRotationSpd = 0.f;
	beginFadeTime = 1.f;
	fadeSize = false;

	minSecondsBetweenParticles = 1.f;
	maxSecondsBetweenParticles = 1.f;
	timer = 0.f;
	nextParticleTime = 0.f;

	layer = 0;
	active = true;
}


dfParticleSystem::~dfParticleSystem(void)
{
}

void dfParticleSystem::Init()
{
	dfComponent::Init();

	renderer = entity->GetComponent<Renderer>();
}

void dfParticleSystem::Update()
{
	dfComponent::Init();
	
	if(active)
	{
		timer += 0.05f; // todo dt

		if(timer > nextParticleTime)
		{
			CreateParticle();
			nextParticleTime =  minSecondsBetweenParticles + (randf() * (maxSecondsBetweenParticles - minSecondsBetweenParticles));
		}
	}

	for(int i = 0; i < pbox.numParticles; i++)
	{
		if(!pbox.particles[i].dead)
		{
			UpdateParticle(pbox.particles[i]);
		}
	}
}

void dfParticleSystem::InitParticle(ParticleInfo &p)
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
	p.rotationSpd = 0;

}

void dfParticleSystem::CreateParticle()
{
	ParticleInfo p;
	InitParticle(p);
	if(useSpawnRect)
	{
		p.pos = vec2(
			(randf() * spawnRect.width) + spawnRect.left,
			(randf() * spawnRect.height) + spawnRect.top);
	}
	else
	{
		p.pos = vec2(spawnPoint.x, spawnPoint.y);
	}
	p.acc = minAcc + (randf() * (maxAcc - minAcc));
	p.color = startColor;
	p.dead = false;
	p.maxSize = minParticleSize + (randf() * (maxParticleSize - minParticleSize));
	p.w = p.maxSize;
	p.h = p.maxSize;
	p.lifespan = minLifespan + (randf() * (maxLifespan - minLifespan));
	p.lifetime = 0;
	p.rotation = minStartRotation + (randf() * (maxStartRotation - minStartRotation));
	p.rotationSpd = minRotationSpd + (randf() * (maxRotationSpd - minRotationSpd));

	dfAssert(textures.size() > 0); // need a texture to attatch to particle, dawg!
	int textureIndex = rand() % textures.size();
	//p.texture = textures[textureIndex];

	for(int i = 0; i < MAX_PARTICLES; i++)
	{
		if(pbox.particles[i].dead)
		{
			pbox.particles[i] = p;
			pbox.numParticles++;
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

	float t = particle.lifetime / particle.lifetime;
	float ct = t;
	if(ct < beginFadeTime)
		ct = 0.f;
	else
		ct = (ct - beginFadeTime) / (1.f - beginFadeTime);

	particle.color = vec4(
		startColor.x + ((endColor.x - startColor.x) * ct),
		startColor.y + ((endColor.y - startColor.y) * ct),
		startColor.z + ((endColor.z - startColor.z) * ct),
		startColor.w + ((endColor.w - startColor.w) * ct));

	if(fadeSize)
	{
		particle.w = particle.maxSize * (1-ct);
		particle.h = particle.maxSize * (1-ct);
	}

	particle.pos.x += particle.veloc.x;
	particle.pos.y += particle.veloc.y;
	particle.veloc.x += particle.acc;
	particle.veloc.y += particle.acc;

	particle.rotation += particle.rotationSpd;
	
}