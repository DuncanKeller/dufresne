#include "Collider.h"


Collider::Collider(void)
{
	stationary = true;
	trigger = false;
}


Collider::~Collider(void)
{
}

void Collider::Init()
{
	dfComponent::Init();
	
	// set default render rectangle
	tf = gameSystem->GetComponent<Transform>();
}

void Collider::Update()
{
	dfComponent::Update();
}
