#include "dfParticleSystem.h"
#include "../Entity/Entity.h"

dfParticleSystem::dfParticleSystem(void)
{
	sInfo.useSpawnRect = false;
	sInfo.spawnRect = Rect();
	sInfo.spawnPoint = vec2(0.f,0.f);
	sInfo.minVeloc = 0.f;
	sInfo.maxVeloc = 0.f;
	sInfo.minLifespan = 0.f;
	sInfo.maxLifespan = 0.f;
	sInfo.minAcc = 0.f;
	sInfo.maxAcc = 0.f;
	sInfo.endColor = vec4(0.f, 0.f, 0.f, 0.f);
	sInfo.minStartRotation = 0.f;
	sInfo.maxStartRotation = 0.f;
	sInfo.minRotationSpd = 0.f;
	sInfo.maxRotationSpd = 0.f;
	sInfo.beginFadeTime = 1.f;
	sInfo.fadeSize = false;

	minSecondsBetweenParticles = 1.f;
	maxSecondsBetweenParticles = 1.f;
	timer = 0.f;
	nextParticleTime = 0.f;

	layer = 0;
	active = true;
	maxActiveParticles = 100;
	numParticles = 0;
	currentParticleCap = 0;

	for(int i = 0; i < MAX_PARTICLES; i++)
	{
		particleRenderers[i].renderInfo.active = false;
	}
}


dfParticleSystem::~dfParticleSystem(void)
{
}

void dfParticleSystem::Init()
{
	dfComponent::Init();

	parentRenderer = entity->GetComponent<Renderer>();
}

void dfParticleSystem::Update()
{
	dfComponent::Init();
	
	if(active)
	{
		timer += dfDeltaTime;

		if(timer > nextParticleTime && numParticles < maxActiveParticles)
		{
			CreateParticle();
			nextParticleTime =  minSecondsBetweenParticles + (dfRand() * (maxSecondsBetweenParticles - minSecondsBetweenParticles));
		}
	}

	for(int i = 0; i < numParticles; i++)
	{
		if(particles[i].color.x == 1 && particles[i].color.y == 1 && particles[i].color.z == 1)
			int fut = 4;

		if(!particles[i].dead)
		{
			UpdateParticle(particles[i], i);
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
	if(sInfo.useSpawnRect)
	{
		p.pos = vec2(
			(dfRand() * sInfo.spawnRect.width) + sInfo.spawnRect.left,
			(dfRand() * sInfo.spawnRect.height) + sInfo.spawnRect.top);
	}
	else
	{
		p.pos = vec2(sInfo.spawnPoint.x, sInfo.spawnPoint.y);
	}
	p.acc = sInfo.minAcc + (dfRand() * (sInfo.maxAcc - sInfo.minAcc));
	int colorIndex = rand() % sInfo.startColors.size();
	p.startColor = sInfo.startColors[colorIndex];
	p.color = p.startColor;
	p.dead = false;
	p.maxSize = sInfo.minParticleSize + (dfRand() * (sInfo.maxParticleSize - sInfo.minParticleSize));
	p.w = p.maxSize;
	p.h = p.maxSize;
	p.lifespan = sInfo.minLifespan + (dfRand() * (sInfo.maxLifespan - sInfo.minLifespan));
	p.lifetime = 0;
	p.rotation = sInfo.minStartRotation + (dfRand() * (sInfo.maxStartRotation - sInfo.minStartRotation));
	p.rotationSpd = sInfo.minRotationSpd + (dfRand() * (sInfo.maxRotationSpd - sInfo.minRotationSpd));
	float newVeloc = dfRand() * (sInfo.maxVeloc - sInfo.minVeloc);
	float xComp = cos((Pi32 / 180.f) * p.rotation) * newVeloc;
	float yComp = sin((Pi32 / 180.f) * p.rotation) * newVeloc;
	p.veloc = vec2(xComp, yComp);

	dfAssert(sInfo.textures.size() > 0); // need a texture to attatch to particle, dawg!
	int textureIndex = rand() % sInfo.textures.size();
	//p.texture = textures[textureIndex];
	p.renderRect = new Rect();
	RectSet(p.pos.x - (p.w / 2.f), p.pos.y - (p.h / 2.f), p.w, p.h, p.renderRect);

	for(int i = 0; i < currentParticleCap + 1 < MAX_PARTICLES ? currentParticleCap + 1 : MAX_PARTICLES; i++)
	{
		if(particles[i].dead)
		{
			particles[i] = p;
			
			particleRenderers[i].renderRect = p.renderRect;
			particleRenderers[i].SetTexture(sInfo.textures[textureIndex]);
			particleRenderers[i].renderInfo.active = true;
			particleRenderers[i].renderInfo.depth = layer;

			for(int cIndex = 0; cIndex < particleRenderers[i].renderInfo.uniforms.size(); cIndex++)
			{
				if(dfStrCmp("rect", particleRenderers[i].renderInfo.uniforms[cIndex].name))
				{
					particleRenderers[i].renderInfo.uniforms[cIndex].valueRect = p.renderRect;
					break;
				}
			}

			numParticles++;
			if(i == currentParticleCap)
				currentParticleCap++;

			return;
		}
	}

	dfWarn("Could not create particle. Max particles!");
}

void dfParticleSystem::UpdateParticle(ParticleInfo &particle, int index)
{
	particle.lifetime += dfDeltaTime;
	if(particle.lifetime > particle.lifespan)
	{
		particleRenderers[index].renderInfo.active = false;
		particle.dead = true;
		delete particle.renderRect;
		numParticles--;
		if(index == currentParticleCap - 1)
			currentParticleCap--;
		return;
	}

	float t = particle.lifetime / particle.lifespan;
	float ct = t;
	if(ct < sInfo.beginFadeTime)
		ct = 0.f;
	else
		ct = (ct - sInfo.beginFadeTime) / (1.f - sInfo.beginFadeTime);

	particle.color = vec4(
		particle.startColor.x + ((sInfo.endColor.x - particle.startColor.x) * ct),
		particle.startColor.y + ((sInfo.endColor.y - particle.startColor.y) * ct),
		particle.startColor.z + ((sInfo.endColor.z - particle.startColor.z) * ct),
		particle.startColor.w + ((sInfo.endColor.w - particle.startColor.w) * ct));
	particleRenderers[index].renderInfo.color = particle.color;

	if(sInfo.fadeSize)
	{
		particle.w = particle.maxSize * (1.f-ct);
		particle.h = particle.maxSize * (1.f-ct);
	}

	particle.pos.x += particle.veloc.x;
	particle.pos.y += particle.veloc.y;
	particle.veloc.x += particle.acc;
	particle.veloc.y += particle.acc;

	particle.rotation += particle.rotationSpd;

	
	RectSet(particle.pos.x - (particle.w / 2.f), particle.pos.y - (particle.h / 2.f), 
		particle.w, particle.h, particle.renderRect);
	
}