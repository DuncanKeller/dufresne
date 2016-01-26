#include "DuFradius.h"

stdEntity* ship;
std::vector<stdEntity*> bullets;
std::vector<dfEnemy*> enemies;
std::vector<SupaLaser*> lasers;

std::vector<dfParticleSystem*> playerParticleList;

const char* laserBeamFrag = ""
	//"#version 130\n"
	//"#extension GL_ARB_explicit_attrib_location : require\n"
	//"#extension GL_ARB_explicit_uniform_location : require\n"
	"in vec2 texture_coordinates;"
	"uniform vec4 inColor;"
	"uniform float time;"
	"uniform vec2 resolution;"
	"uniform float life;"
	"uniform float endLife;"
	"out vec4 frag_color;"
	"void main()"
	"{"
	"	float power = 2;"
	"	float timeModifier = mod(time * 1.3, 0.75);"
	"	power += timeModifier;"
	"	float magic = mod(time,1);"
	"	frag_color = vec4(1,"
	"		abs((texture_coordinates.y - .5) * power),"
	"		timeModifier,"
	"		1);"
	""
	""
	"	float lifeMod = 1;"
	"	if(life < 0.2)"
	"	{"
	"		lifeMod = life * 5;"
	"	}"
	"	else if(life > endLife - 0.4)"
	"	{"
	"		lifeMod = 1 - ((life - (endLife - 0.4)) * 2.5);"
	"	}"
	""
	"	float arcXMod = 1;"
	"	if(texture_coordinates.x * resolution.x > resolution.x - 200)"
	"	{"
	"		arcXMod = 1 - ((texture_coordinates.x * resolution.x) - (resolution.x - 200)) / 100.0;"
	"	}"
	""
	"	float arcTimer =  (abs(mod(time, 2) - 1) * 5) + 25;"
	"	float arc = sin((texture_coordinates.x * arcTimer) + (time * 40));"
	"	float arc2 = sin((texture_coordinates.x * 40) + (time * 90));"
	"	vec4 waveform = vec4(1,1,1,1);"
	"	if(abs(texture_coordinates.y - .5) * 2 > ((arc + 1.7) / 2.7) * lifeMod * arcXMod && "
	"		abs(texture_coordinates.y - .5) * 2 > ((arc2 + 1.7) / 2.7) * lifeMod * arcXMod) "
	"		frag_color.a = 0;"
	//"	frag_color = vec4(arcXMod,0,0,1);"
	"}"
	"";

const char* fradiusEntityFrag = ""
	//"#version 130\n"
	//"#extension GL_ARB_explicit_attrib_location : require\n"
	//"#extension GL_ARB_explicit_uniform_location : require\n"
	"in vec2 texture_coordinates;"
	"uniform sampler2D basic_texture;"
	"uniform vec2 atlasPos,spriteSize;"
	"uniform vec4 inColor;"
	"out vec4 frag_color;"
	"void main()"
	"{"
	"	vec2 realCoord = atlasPos + spriteSize * texture_coordinates;"
	"	vec4 texel = texture2D(basic_texture, realCoord);"
	"	frag_color = vec4(texel.r * inColor.r, texel.g * inColor.g, texel.b * inColor.b, texel.a * inColor.a);"
	"}"
	"";

void InitLevel1Scene()
{
	ship = sceneMan.CreateSceneObject<stdEntity>();
	ship->Init();
	ship->render.SetTexture(assMan.GetTexture(L"fart\\dufradius\\ship.png"));
	ship->tf.SetPos(100, 100);
	ship->render.renderInfo.depth = 10;

	SetupParticles();
}

void DufradiuInitGame()
{
	
	input.AddMappedAnalogInput(L"move-x", &input.keyboard.arrowLeft, &input.keyboard.arrowRight);
	input.AddMappedAnalogInput(L"move-y", &input.keyboard.arrowUp, &input.keyboard.arrowDown);
	input.AddMappedDigitalButton(L"fire", &input.keyboard.spacebar);
	input.AddMappedDigitalButton(L"fire", &input.keyboard.z);
	input.AddMappedDigitalButton(L"fire", &input.keyboard.a);
	
	input.AddMappedDigitalButton(L"test", &input.keyboard.g);
	input.AddMappedDigitalButton(L"test2", &input.keyboard.h);
	input.AddMappedDigitalButton(L"test3", &input.keyboard.j);

	dfScene* scene1 = sceneMan.CreateScene("level 1");
	scene1->setupFunc = InitLevel1Scene;
	sceneMan.LoadScene("level 1");
}

void SetupParticles()
{
	playerParticleList.clear();
	dfParticleSystem* playerParticles =  new dfParticleSystem(); 
	playerParticles->minSecondsBetweenParticles = 0.01f;
	playerParticles->maxSecondsBetweenParticles = 0.01f;
	playerParticles->maxActiveParticles = 1000;
	playerParticles->layer = 5;
	playerParticles->sInfo.spawnPoint = vec2(0, 0);
	playerParticles->sInfo.minVeloc = 300;
	playerParticles->sInfo.maxVeloc = 300;
	playerParticles->sInfo.minLifespan = 0.2f;
	playerParticles->sInfo.maxLifespan = 0.2f;
	playerParticles->sInfo.minAcc = 0;
	playerParticles->sInfo.maxAcc = 0;
	playerParticles->sInfo.startColors.push_back(vec4(1,0,0,1));
	playerParticles->sInfo.beginFadeTime = .7f;
	playerParticles->sInfo.minStartRotation = 180;
	playerParticles->sInfo.maxStartRotation = 180;
	playerParticles->sInfo.minRotationSpd = 0;
	playerParticles->sInfo.maxRotationSpd = 0;
	playerParticles->sInfo.minParticleSize = 20;
	playerParticles->sInfo.maxParticleSize = 20;
	playerParticles->sInfo.fadeSize = 0;
	playerParticles->sInfo.textures.push_back(assMan.GetTexture(L"fart\\dufradius\\particle-gradient.png"));
	ship->RegisterComponent(playerParticles);
	playerParticleList.push_back(playerParticles);

	dfParticleSystem* playerParticles2 =  new dfParticleSystem(); 
	playerParticles2->minSecondsBetweenParticles = 0.1f;
	playerParticles2->maxSecondsBetweenParticles = 0.1f;
	playerParticles2->maxActiveParticles = 1000;
	playerParticles2->layer = 4;
	playerParticles2->sInfo.spawnPoint = vec2(0, 0);
	playerParticles2->sInfo.minVeloc = 9;
	playerParticles2->sInfo.maxVeloc = 9;
	playerParticles2->sInfo.minLifespan = 0.9f;
	playerParticles2->sInfo.maxLifespan = 0.9f;
	playerParticles2->sInfo.minAcc = 0;
	playerParticles2->sInfo.maxAcc = 0;
	playerParticles2->sInfo.startColors.push_back(vec4(0.2,0.2,0.2,0.9));
	playerParticles2->sInfo.beginFadeTime = .9f;
	playerParticles2->sInfo.minStartRotation = 160;
	playerParticles2->sInfo.maxStartRotation = 200;
	playerParticles2->sInfo.minRotationSpd = 0;
	playerParticles2->sInfo.maxRotationSpd = 0;
	playerParticles2->sInfo.minParticleSize = 50;
	playerParticles2->sInfo.maxParticleSize = 70;
	playerParticles2->sInfo.fadeSize = 0;
	playerParticles2->sInfo.textures.push_back(assMan.GetTexture(L"fart\\dufradius\\particle-gradient.png"));
	ship->RegisterComponent(playerParticles2);
	playerParticleList.push_back(playerParticles2);
}

void ShootShip(int shipNum)
{
	stdEntity* bullet = sceneMan.CreateSceneObject<stdEntity>();
	bullet->Init();
	bullet->render.SetTexture(assMan.GetTexture(L"fart\\dude.png"));
	bullet->tf.SetPos(ship->tf.rectangle.left, ship->tf.rectangle.top);
	bullet->render.renderInfo.depth = 10;
	bullet->bc.collisionRect = &bullet->tf.rectangle;
	bullets.push_back(bullet);
}

void MoveShip(int shipNum)
{
	float x = input.GetMappedAxis(L"move-x");
	float y = input.GetMappedAxis(L"move-y");
	
	ship->tf.MovePos(x * shipSpd * dfDeltaTime, y * shipSpd * dfDeltaTime); 
	
	if(ship->tf.rectangle.left < 0)
		ship->tf.SetPos(0.f, ship->tf.rectangle.top);
	if(ship->tf.rectangle.right > GameResolution.x)
		ship->tf.SetPos(GameResolution.x - ship->tf.rectangle.width, ship->tf.rectangle.top);
	if(ship->tf.rectangle.top < 0)
		ship->tf.SetPos(ship->tf.rectangle.left, 0.f);
	if(ship->tf.rectangle.bottom > GameResolution.y)
		ship->tf.SetPos(ship->tf.rectangle.left, GameResolution.y - ship->tf.rectangle.height);

	if(input.GetMappedButton(L"fire").tapped)
	{
		ShootShip(0);
	}

	for(int i = 0; i < playerParticleList.size(); i++)
	{
		playerParticleList[i]->sInfo.spawnPoint = vec2(
			ship->tf.rectangle.left, ship->tf.rectangle.bottom - ship->tf.rectangle.height / 2);
	}
}

void ProcessBullets()
{
	std::vector<int> removeMe;
	for(int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->tf.MovePos(bulletSpd * dfDeltaTime, 0.f);
		if(bullets[i]->tf.rectangle.left > GameResolution.x)
			removeMe.push_back(i);
	}

	for(int i = 0; i < removeMe.size(); i++)
	{
		bullets.erase(bullets.begin() + (removeMe[i] ));

		for(int ii = 0; ii < removeMe.size(); ii++)
		{
			if(removeMe[ii] > removeMe[i])
				removeMe[i] --;
		}
	}
}

void DufradiusUpdate()
{
	MoveShip(0);
	ProcessBullets();
	UpdateEnemies();
	UpdateLasers();

	if(input.GetMappedButton(L"test").tapped)
	{
		SetupMegaCharger(300, 0.4f);
	}
	if(input.GetMappedButton(L"test2").tapped)
	{
		SetupMiniPather(300, 200);
	}
	if(input.GetMappedButton(L"test3").tapped)
	{
		SetupSwerver(300, 150);
	}

	Rect r;
	RectSet(0,0,GameResolution.x,GameResolution.y, &r);
	RenderSystem::DrawRect(r, vec4(0,0,0,1), 0);
}

void SetupMiniPather(float lHeight, float rHeight)
{
	EnemyPath p;
	float leftSide = 400.f;
	float rightSide = 600.f;
	
	p.leftBoundary = vec2(leftSide, lHeight);
	p.rightBoundary = vec2(rightSide, rHeight);

	p.middleSlope = (p.rightBoundary.y - p.leftBoundary.y) / (p.rightBoundary.x - p.leftBoundary.x);
	p.middleOffset = p.leftBoundary.y / (p.middleSlope * p.leftBoundary.x);

	dfEnemy* enemy = new dfEnemy();
	enemy->entity = sceneMan.CreateSceneObject<stdEntity>();
	enemy->entity->Init();
	enemy->entity->render.InitSprite(assMan.GetTexture(L"fart\\dufradius\\enemy2.png"), 1, 1, 0, 0);
	enemy->entity->render.SetShader(defaultVert, fradiusEntityFrag);
	enemy->entity->render.SetRenderRect(&enemy->renderRect);
	enemy->entity->tf.SetPos(GameResolution.x + 5, p.rightBoundary.y);
	enemy->entity->bc.collisionRect = &enemy->entity->tf.rectangle;
	enemy->path = p;

	enemy->spd = 300.f;
	enemy->type = miniPather;
	enemy->health = 1;
	
	BasicEnemyInit(enemy);

	enemy->entity->render.renderInfo.depth = 10;
	enemies.push_back(enemy);
}

void SetupSwerver(float height, float swrvAmnt)
{
	dfEnemySwerve sw;
	sw.startingHeight = height;
	sw.swrvAmnt = swrvAmnt;
	sw.veloc  = 0.f;
	sw.swrvSpd = 7.f;

	dfEnemy* enemy = new dfEnemy();
	enemy->entity = sceneMan.CreateSceneObject<stdEntity>();
	enemy->entity->Init();
	enemy->entity->render.InitSprite(assMan.GetTexture(L"fart\\dufradius\\enemy3.png"), 1, 1, 0, 0);
	enemy->entity->render.SetShader(defaultVert, fradiusEntityFrag);
	enemy->entity->render.SetRenderRect(&enemy->renderRect);
	enemy->entity->tf.SetPos(GameResolution.x + 5, height);
	enemy->entity->bc.collisionRect = &enemy->entity->tf.rectangle;
	enemy->swerve = sw;

	enemy->spd = 200.f;
	enemy->type = swerver;
	enemy->health = 2;

	BasicEnemyInit(enemy);

	enemy->entity->render.renderInfo.depth = 10;
	enemies.push_back(enemy);
}


void SetupMegaCharger(float height, float waitTime)
{
	dfEnemyCharge c;
	c.timer = waitTime;
	c.doneFiring = false;
	c.doneMoving = false;

	dfEnemy* enemy = new dfEnemy();
	enemy->entity = sceneMan.CreateSceneObject<stdEntity>();
	enemy->entity->Init();
	enemy->entity->render.InitSprite(assMan.GetTexture(L"fart\\dufradius\\enemy4.png"), 1, 1, 0, 0);
	enemy->entity->render.SetShader(defaultVert, fradiusEntityFrag);
	enemy->entity->render.SetRenderRect(&enemy->renderRect);
	enemy->entity->tf.SetPos(GameResolution.x + 5, height);
	enemy->entity->bc.collisionRect = &enemy->entity->tf.rectangle;
	enemy->charge = c;

	enemy->spd = 50.f;
	enemy->type = megaCharger;
	enemy->health = 10;
	
	BasicEnemyInit(enemy);

	enemy->entity->render.renderInfo.depth = 10;
	enemies.push_back(enemy);
}

void SetupElectric(float height, float offsetX, float offsetY)
{
	dfEnemyElectric ec1;
	dfEnemyElectric ec2;

	dfEnemy* enemy1 = new dfEnemy();
	enemy1->entity = sceneMan.CreateSceneObject<stdEntity>();
	enemy1->entity->Init();
	enemy1->entity->render.InitSprite(assMan.GetTexture(L"fart\\dufradius\\enemy5.png"), 1, 1, 0, 0);
	enemy1->entity->render.SetShader(defaultVert, fradiusEntityFrag);
	enemy1->entity->render.SetRenderRect(&enemy1->renderRect);
	enemy1->entity->bc.collisionRect = &enemy1->entity->tf.rectangle;
	enemy1->entity->tf.SetPos(GameResolution.x + 5, height);

	
	dfEnemy* enemy2 = new dfEnemy();
	enemy2->entity = sceneMan.CreateSceneObject<stdEntity>();
	enemy2->entity->Init();
	enemy2->entity->render.InitSprite(assMan.GetTexture(L"fart\\dufradius\\enemy5.png"), 1, 1, 0, 0);
	enemy2->entity->render.SetShader(defaultVert, fradiusEntityFrag);
	enemy2->entity->render.SetRenderRect(&enemy2->renderRect);
	enemy2->entity->tf.SetPos(GameResolution.x + 5 + offsetX, height + offsetY);
	enemy2->entity->bc.collisionRect = &enemy2->entity->tf.rectangle;

	enemy1->spd = 100.f;
	enemy1->type = electric;
	enemy1->health = 3;

	enemy2->spd = 100.f;
	enemy2->type = electric;
	enemy2->health = 3;
	
	enemy1->entity->render.renderInfo.depth = 10;
	enemy2->entity->render.renderInfo.depth = 10;
	
	ec1.linkedEnemy = enemy2;
	ec1.leader = true;
	ec2.linkedEnemy = enemy1;
	ec2.leader = false;

	enemy1->elec = ec1;
	enemy2->elec = ec2;
	
	BasicEnemyInit(enemy1);
	BasicEnemyInit(enemy2);

	enemies.push_back(enemy1);
	enemies.push_back(enemy2);
}

void BasicEnemyInit(dfEnemy* e)
{
	e->shakeTime = 0;
	e->flashTime = 0;
}

void UpdateEnemies()
{
	std::vector<int> removeMe;
	std::vector<int> removeBullets;

	for(int i = 0; i < enemies.size(); i++)
	{
		stdEntity* e = enemies[i]->entity;

		enemies[i]->renderRect = e->tf.rectangle;

		if(enemies[i]->shakeTime > 0)
		{
			float mod =  enemies[i]->shakeTime / ENEMY_MAX_SHAKE;
			vec2 amnt = vec2(
				dfRand(-10 * mod, 10 * mod),
				dfRand(-10 * mod, 10 * mod));

			RectMove(amnt, &enemies[i]->renderRect);

			enemies[i]->shakeTime -= dfDeltaTime;
		}

		if(enemies[i]->flashTime > 0)
		{
			bool flash = fmod(enemies[i]->flashTime, 0.2f) > 0.1f;
			if(flash)
				e->render.renderInfo.color = vec4(1,0,0,1);
			else
				e->render.renderInfo.color = vec4(1,1,1,1);

			enemies[i]->flashTime -= dfDeltaTime;
		}
		else
			e->render.renderInfo.color = vec4(1,1,1,1);
		


		if(enemies[i]->type == miniPather)
		{
			float yPos = 0.f;
			if(e->tf.rectangle.left > enemies[i]->path.rightBoundary.x)
				yPos = enemies[i]->path.rightBoundary.y;
			else if(e->tf.rectangle.left < enemies[i]->path.leftBoundary.x)
				yPos = enemies[i]->path.leftBoundary.y;
			else
				yPos = (enemies[i]->path.middleSlope * (e->tf.rectangle.left - enemies[i]->path.leftBoundary.x))
					+ enemies[i]->path.leftBoundary.y;

			e->tf.SetPos(
				e->tf.rectangle.left - (dfDeltaTime * enemies[i]->spd),
				yPos);
		}
		else if(enemies[i]->type == swerver)
		{
			enemies[i]->swerve.veloc = sin(dfTotalTime * enemies[i]->swerve.swrvSpd);

			e->tf.SetPos(
				e->tf.rectangle.left - (dfDeltaTime * enemies[i]->spd),
				enemies[i]->swerve.startingHeight + enemies[i]->swerve.veloc *
				enemies[i]->swerve.swrvAmnt);
		}
		else if(enemies[i]->type == megaCharger)
		{
			if(e->tf.rectangle.left > GameResolution.x - 120.f ||
				enemies[i]->charge.doneFiring)
			{
				e->tf.SetPos(
					e->tf.rectangle.left - (dfDeltaTime * enemies[i]->spd),
					e->tf.rectangle.top);
			}
			else
			{
				e->tf.SetPos(
					GameResolution.x - 120.f,
					e->tf.rectangle.top);

				enemies[i]->charge.timer -= dfDeltaTime;
				if(enemies[i]->charge.doneMoving && enemies[i]->charge.timer < -5.f)
				{
					enemies[i]->charge.doneFiring = true;
				}
				else if(enemies[i]->charge.timer <= 0 && !enemies[i]->charge.doneMoving)
				{
					ChargerFire(*enemies[i]);
					enemies[i]->charge.doneMoving = true;
				}
			}
		}
		else if(enemies[i]->type == electric)
		{
			e->tf.SetPos(
					e->tf.rectangle.left - (dfDeltaTime * enemies[i]->spd),
					e->tf.rectangle.top);

			if(enemies[i]->elec.leader)
			{
				if(enemies[i]->elec.linkedEnemy != NULL)
				{
					dfLine line;
					line.a = vec2(e->tf.rectangle.left, e->tf.rectangle.top);
					line.b = vec2(enemies[i]->elec.linkedEnemy->entity->tf.rectangle.left, 
						enemies[i]->elec.linkedEnemy->entity->tf.rectangle.top);
					line.width = 5.f;
					RenderSystem::DrawLine(line, vec4(1.f, 1.f, 0.f, 1.f), 15);

				}
			}
		}

		if(e->tf.rectangle.right < -100.f)
			removeMe.push_back(i);

		for(int ii = 0; ii < bullets.size(); ii++)
		{
	 		if(RectIntersects(*bullets[ii]->bc.collisionRect, *e->bc.collisionRect))
			{
				bool alreadyInThere = false;
				for(int iii = 0; iii < removeBullets.size(); iii++)
				{
					if(removeBullets[iii] == ii)
						alreadyInThere = true; break;
				}
				if(!alreadyInThere)
					removeBullets.push_back(ii);
				
				enemies[i]->shakeTime += ENEMY_MAX_SHAKE;
				enemies[i]->flashTime = 0.4f;

 				enemies[i]->health--;
				if(enemies[i]->health <= 0)
					removeMe.push_back(i);
			}
			else if(bullets[ii]->tf.rectangle.left > GameResolution.x)
				removeBullets.push_back(ii);

		}
	}

	for(int i = 0; i < removeBullets.size(); i++)
	{
		sceneMan.RemoveSceneObject(bullets[removeBullets[i]]);
		bullets.erase(bullets.begin() + (removeBullets[i]));

		for(int ii = 0; ii < removeBullets.size(); ii++)
		{
			if(removeBullets[ii] > removeBullets[i])
				removeBullets[i] --;
		}
	}

	for(int i = 0; i < removeMe.size(); i++)
	{
		if(enemies[removeMe[i]]->type == electric &&
			enemies[removeMe[i]]->elec.linkedEnemy != NULL)
			enemies[removeMe[i]]->elec.linkedEnemy->elec.linkedEnemy = 0;

		sceneMan.RemoveSceneObject(enemies[removeMe[i]]->entity);

		enemies.erase(enemies.begin() + (removeMe[i]));

		for(int ii = 0; ii < removeMe.size(); ii++)
		{
			if(removeMe[ii] > removeMe[i])
				removeMe[i] --;
		}
	}
}


void ChargerFire(dfEnemy e)
{
	SupaLaser* lasoo = new SupaLaser();
	lasoo->timeAlive = 0.f;
	lasoo->lifeTime = 3.f;

	stdEntity* ent = sceneMan.CreateSceneObject<stdEntity>();
	ent->Init();
	ent->render.SetTexture(assMan.GetTexture(L"fart\\dude.png"));
	ent->tf.SetRect(0,e.entity->tf.rectangle.top,
		GameResolution.x, 100);
	ent->render.SetShader(defaultVert, laserBeamFrag);
	ent->render.renderInfo.depth = 10;
	
	ent->render.AddUniformFloat("life", &lasoo->timeAlive);
	ent->render.AddUniformFloat("endLife", &lasoo->lifeTime);

	lasoo->ent = ent;

	lasers.push_back(lasoo);
}

void UpdateLasers()
{
	std::vector<int> removeMe;
	int numRemvoed = 0;

	for(int i = 0; i < lasers.size(); i++)
	{
		lasers[i]->timeAlive += dfDeltaTime;

		if(lasers[i]->timeAlive > lasers[i]->lifeTime)
			removeMe.push_back(i);

	}

	for(int i = 0; i < removeMe.size(); i++)
	{
		sceneMan.RemoveSceneObject(lasers[removeMe[i]]->ent);

		lasers.erase(lasers.begin() + (removeMe[i] - numRemvoed));
		numRemvoed++;
	}
}