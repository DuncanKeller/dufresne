#include "dfTile.h"


dfTile::dfTile(void)
{
	RegisterComponent(&tf);
	RegisterComponent(&render);
	RegisterComponent(&bc);
	bc.stationary = true;
	bc.enabled = false;
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

void dfTile::InterpretProperty(const char* name, const char* value)
{
	if(dfStrCmp(name, "collision"))
	{
		bool val = dfStringToBool(value);
		bc.enabled = val;
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