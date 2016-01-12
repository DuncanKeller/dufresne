#include "stdEntity.h"

stdEntity::stdEntity(void)
{
}


stdEntity::~stdEntity(void)
{
}

void stdEntity::Init()
{
	Entity::Init();
	RegisterComponent(&tf);
	RegisterComponent(&render);
	RegisterComponent(&bc);
	RegisterComponent(&animComp);
}

void stdEntity::Update()
{
	Entity::Update();

}