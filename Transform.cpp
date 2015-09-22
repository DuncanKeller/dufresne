#include "Transform.h"


Transform::Transform(void)
{
}


Transform::~Transform(void)
{
	dfComponent::~dfComponent();
}

void Transform::SetPos(float x, float y, float z)
{
	pos.x = x;
	pos.y = y;
	pos.z = z;
	UpdateMatrix();
}

void Transform::SetPos(Vec3 p)
{
	pos.x = p.x;
	pos.y = p.y;
	pos.z = p.z;
	UpdateMatrix();
}

void Transform::UpdateMatrix()
{
	matrix.m[0] = 0.f;
	matrix.m[1] = 0.f;
	matrix.m[2] = 0.f;
	matrix.m[3] = pos.x;

	matrix.m[4] = 0.f;
	matrix.m[5] = 0.f;
	matrix.m[6] = 0.f;
	matrix.m[7] = pos.y;

	matrix.m[8] = 0.f;
	matrix.m[9] = 0.f;
	matrix.m[10] = 0.f;
	matrix.m[11] = pos.z;

	matrix.m[12] = 0.f;
	matrix.m[13] = 0.f;
	matrix.m[14] = 0.f;
	matrix.m[15] = 0.f;
}