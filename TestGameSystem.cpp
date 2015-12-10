#include "TestGameSystem.h"


TestEntity::TestEntity(void)
{
}


TestEntity::~TestEntity(void)
{
}


void TestEntity::Init()
{
	RegisterComponent(&tf);

	render.renderInfo.matrix = &tf.matrix;


	// was model matrix, now coords...
	//render.renderInfo.uniforms[0].valueFloat = &(render.renderInfo.matrix->m[0]);

	RegisterComponent(&render);
	
	bc = BoxCollider();
	RegisterComponent(&bc);

	Entity::Init();
	
	

	TextureInfo textureFile = assMan.GetTexture(L"fart\\test-anim.png");
	
	render.InitSprite(textureFile, 4, 3, 0, 0);

	animComp = new dfAnimator(L"fart\\test-anim_animations.json");
	RegisterComponent(animComp);

	particleSys = new dfParticleSystem();
	RegisterComponent(particleSys);
	particleSys->layer = 300;
	particleSys->spawnPoint = vec2(100, 100);
	particleSys->minVeloc = 3;
	particleSys->maxVeloc = 6;
	particleSys->minLifespan = 1;
	particleSys->maxLifespan = 1;
	particleSys->minAcc = 0;
	particleSys->maxAcc = 0;
	particleSys->startColors.push_back(vec4(1,0,0,1));
	particleSys->startColors.push_back(vec4(0,0,1,1));
	particleSys->startColors.push_back(vec4(0,1,0,1));
	particleSys->beginFadeTime = .9f;
	particleSys->minStartRotation = -180;
	particleSys->maxStartRotation = 0;
	particleSys->minRotationSpd = 0;
	particleSys->maxRotationSpd = 0;
	particleSys->minParticleSize = 5;
	particleSys->maxParticleSize = 15;
	particleSys->fadeSize = 1;
	particleSys->textures.push_back(assMan.GetTexture(L"fart\\test-particle.png"));
}

void TestEntity::Update()
{
	Entity::Update();

	if(input.keyboard.arrowUp.buttonDown)
	{
		RectMove(0, -5.1f, &tf.rectangle);
		animComp->Play("walk-up");
	}
	if(input.keyboard.arrowDown.buttonDown)
	{
		RectMove(0, 5, &tf.rectangle);
		animComp->Play("walk-down");
	}
	if(input.keyboard.arrowLeft.buttonDown)
	{
		RectMove(-5, 0, &tf.rectangle);
		animComp->Play("walk-left");
	}
	if(input.keyboard.arrowRight.buttonDown)
	{
		RectMove( 5, 0, &tf.rectangle);
		animComp->Play("walk-right");
	}

	particleSys->spawnPoint = tf.rectangle.pos;
	particleSys->spawnPoint.x += tf.rectangle.width / 2;
}

// todo
// notes
// 1
// render.renderInfo.matrix = &tf.matrix;
// OK, obviously I want to use the tf matrix as the render matrix. 
// any way to make this quicker/easier for a user?
// 2
// having to re-set that matrix uniform to point to the tf matrix is a hassle
// render.renderInfo.uniforms[0].valueFloat = &(render.renderInfo.matrix->m[0]);
// can we automate this somehow?