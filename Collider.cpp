#include "Collider.h"
#include "Entity.h"

Collider::Collider(void)
{
	stationary = true;
	trigger = false;
	enabled = true;
}


Collider::~Collider(void)
{
}

void Collider::Init()
{
	dfComponent::Init();
	
	// set default render rectangle
	tf = entity->GetComponent<Transform>();
}

void Collider::Update()
{
	dfComponent::Update();
}

void Collider::SetEnabled(bool val)
{
	enabled = val;
}