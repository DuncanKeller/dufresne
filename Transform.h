#pragma once
#include "dfcomponent.h"
#include "STDUNC.h"
#include "MatMath.h"

class Transform :
	public dfComponent
{
public:
	// todo cleanup, remove pos and scale, just use rect? Keep rot, though.
	// OR have matrix as a second option.
	// hmmmm....
	Transform(void);
	virtual ~Transform(void);

	virtual void Init();
	virtual void Update();

	vec3 pos;
	vec3 rotation;
	vec3 scale;
	Rect rectangle;

	void SetPos(float x, float y);
	void SetPos(vec2 p);
	void SetPos(float x, float y, float z);
	void SetPos(vec3 p);
	void MovePos(float x, float y);
	void MovePos(vec2 p);

	void SetScale(float x, float y);
	void SetScale(vec2 p);
	void SetScale(float x, float y, float z);
	void SetScale(vec3 p);

	void SetRotation(float r);

	void UpdateMatrix();

	mat4 matrix;

	vec2 lastFramePosition;
	vec2 deltaPosition;
};