#include "Transform.h"


Transform::Transform(void)
{
	pos.x = 0; pos.y = 0; pos.z = 0;
	scale.x = 1; scale.y = 1; scale.z = 1;
	rotation.x = 0; rotation.y = 0; rotation.z = 0;
	rectangle.pos = vec2(0,0);
	rectangle.size = vec2(50,50);
	UpdateRectMembers(rectangle); // todo replace with CreateRect method. I don't like updaterectmemebers being called outside of stdunc
}


Transform::~Transform(void)
{
	dfComponent::~dfComponent();
}

void Transform::SetPos(float x, float y)
{
	pos.x = x;
	pos.y = y;
	UpdateMatrix();
}
	
void Transform::SetPos(vec2 p)
{
	pos.x = p.x;
	pos.y = p.y;
	UpdateMatrix();
}

void Transform::SetPos(float x, float y, float z)
{
	pos.x = x;
	pos.y = y;
	pos.z = z;
	UpdateMatrix();
}

void Transform::SetPos(vec3 p)
{
	pos.x = p.x;
	pos.y = p.y;
	pos.z = p.z;
	UpdateMatrix();
}

void Transform::SetScale(float x, float y)
{
	scale.x = x;
	scale.y = y;
	UpdateMatrix();
}

void Transform::SetScale(vec2 p)
{
	scale.x = p.x;
	scale.y = p.y;
	UpdateMatrix();
}

void Transform::SetScale(float x, float y, float z)
{
	scale.x = x;
	scale.y = y;
	scale.z = z;
	UpdateMatrix();
}

void Transform::SetScale(vec3 p)
{
	scale.x = p.x;
	scale.y = p.y;
	scale.z = p.z;
	UpdateMatrix();
}

void Transform::UpdateMatrix()
{
	matrix.m[0] = scale.x;
	matrix.m[1] = 0.f;
	matrix.m[2] = 0.f;
	matrix.m[3] = 0.f;

	matrix.m[4] = 0.f;
	matrix.m[5] = scale.y;
	matrix.m[6] = 0.f;
	matrix.m[7] = 0.f;

	matrix.m[8] = 0.f;
	matrix.m[9] = 0.f;
	matrix.m[10] = 1.f;
	matrix.m[11] = 0.f;

	matrix.m[12] = pos.x;
	matrix.m[13] = pos.y;
	matrix.m[14] = pos.z;
	matrix.m[15] = 1.f;
}
