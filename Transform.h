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
	vec3 pos;
	vec3 rotation;
	vec3 scale;

	void SetPos(float x, float y);
	void SetPos(vec2 p);
	void SetPos(float x, float y, float z);
	void SetPos(vec3 p);

	void SetScale(float x, float y);
	void SetScale(vec2 p);
	void SetScale(float x, float y, float z);
	void SetScale(vec3 p);

	void SetRotation(float r);

	void UpdateMatrix();

	mat4 matrix;
};