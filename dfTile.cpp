#include "dfTile.h"


dfTile::dfTile(void)
{
	RegisterComponent(&tf);
	RegisterComponent(&render);
}


dfTile::~dfTile(void)
{
}


void dfTile::Init()
{
	GameSystem::Init();

}

void dfTile::Update()
{
	GameSystem::Update();

}

void dfTile::AddCollision(Collider* cd)
{
	colliders.push_back(cd);
	RegisterComponent(cd);
	cd->SetEnabled(false);
}

void dfTile::InterpretProperty(const char* name, const char* value)
{
	if(dfStrCmp(name, "collision"))
	{
		bool val = dfStringToBool(value);
		if(val)
		{
			BoxCollider* bc = new BoxCollider();
			AddCollision(bc);
			bc->collisionRect = &tf.rectangle;
		}
	}
	else if(dfStrCmp(name, "visible"))
	{
		bool val = dfStringToBool(value);
		render.visible = val;
	}
	else if(dfStrCmp(name, "layer"))
	{
		int val = dfStringToInt(value, dfStrLen(value));
		render.renderInfo.depth = val;
	}
}