#pragma once
#include <math.h>
#include "STDUNC.h"

struct mat4 {
	mat4 ();
	mat4 (float a, float b, float c, float d,
				float e, float f, float g, float h,
				float i, float j, float k, float l,
				float mm, float n, float o, float p);/*
	vec4 operator* (const vec4& rhs);*/
	mat4 operator* (const mat4& rhs);
	/*mat4& operator= (const mat4& rhs);*/
	float m[16];
};
/*
struct vec3 {
	vec3 ();
	vec3 (float x, float y, float z);
	void normalize();
	float v[3];
};

struct vec2 {
	vec2();
	vec2(float x, float y);
	vec2(vec2&);
	bool operator== (vec2&);
	float dot(vec2);
	float dot(float x, float y);
	void normalize();
	float x;
	float y;
};
*/
class MatMath
{
public:
	MatMath(void);
	~MatMath(void);
	static mat4 identity_mat4();
	static mat4 zero_mat4 ();
	static mat4 translate(const mat4& m, const vec3& v);
	static float dot(float x1, float y1, float z1, float x2, float y2, float z2);
};

