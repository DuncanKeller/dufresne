#include "dfTile.h"


dfTile::dfTile(void)
{
	RegisterComponent(&tf);
	RegisterComponent(&render);
	RegisterComponent(&bc);
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
