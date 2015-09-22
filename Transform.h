#pragma once
#include "dfcomponent.h"
#include "STDUNC.h"
#include "MatMath.h"

class Transform :
	public dfComponent
{
public:
	Transform(void);
	virtual ~Transform(void);
	Vec3 pos;
	Vec3 rotation;
	Vec3 scale;

	void SetPos(float x, float y, float z);
	void SetPos(Vec3 p);

	void UpdateMatrix();

	mat4 matrix;
};