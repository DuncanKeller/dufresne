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
	/*
	particleSys = new dfParticleSystem();
	RegisterComponent(particleSys);
	particleSys->layer = 300;
	particleSys->sInfo.spawnPoint = vec2(100, 100);
	particleSys->sInfo.minVeloc = 3;
	particleSys->sInfo.maxVeloc = 6;
	particleSys->sInfo.minLifespan = 1;
	particleSys->sInfo.maxLifespan = 1;
	particleSys->sInfo.minAcc = 0;
	particleSys->sInfo.maxAcc = 0;
	particleSys->sInfo.startColors.push_back(vec4(1,0,0,1));
	particleSys->sInfo.startColors.push_back(vec4(0,0,1,1));
	particleSys->sInfo.startColors.push_back(vec4(0,1,0,1));
	particleSys->sInfo.beginFadeTime = .9f;
	particleSys->sInfo.minStartRotation = -180;
	particleSys->sInfo.maxStartRotation = 0;
	particleSys->sInfo.minRotationSpd = 0;
	particleSys->sInfo.maxRotationSpd = 0;
	particleSys->sInfo.minParticleSize = 5;
	particleSys->sInfo.maxParticleSize = 15;
	particleSys->sInfo.fadeSize = 1;
	particleSys->sInfo.textures.push_back(assMan.GetTexture(L"fart\\test-particle.png"));
	*/
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

	//particleSys->sInfo.spawnPoint = tf.rectangle.pos;
	//particleSys->sInfo.spawnPoint.x += tf.rectangle.width / 2;
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