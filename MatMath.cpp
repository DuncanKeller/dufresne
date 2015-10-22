#include "MatMath.h"

// constructors
MatMath::MatMath(void)
{
}


MatMath::~MatMath(void)
{
}
/*
vec3::vec3() {}

vec3::vec3(float a, float b, float c)
{
	v[0] = a; v[1] = b; v[2] = c;
}

void vec3::normalize()
{
	float magnitude = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	v[0] /= magnitude; v[1] /= magnitude; v[2] /= magnitude;
}

vec2::vec2() {}

vec2::vec2(float x, float y)
{
	vec2::x = x;
	vec2::y = y;
}

vec2::vec2(vec2& copyFrom)
{
	vec2::x = copyFrom.x;
	vec2::y = copyFrom.y;
}

bool vec2::operator==(vec2& isEqual)
{
	return vec2::x == isEqual.x && vec2::y == isEqual.y;
}

void vec2::normalize()
{
	float magnitude = sqrt(x * x + y * y);
	x /= magnitude;
	y /= magnitude;
}

float vec2::dot(vec2 vec)
{
	return x * vec.x + y * vec.y;
}

float vec2::dot(float x2, float y2)
{
	return x * x2 + y * y2;
}
*/
mat4::mat4() {}

// note: entered in rows, but stored in columns
mat4::mat4 (float a, float b, float c, float d,
						float e, float f, float g, float h,
						float i, float j, float k, float l,
						float mm, float n, float o, float p) 
{
	m[0] = a; m[1] = e; m[2] = i; m[3] = mm;
	m[4] = b; m[5] = f; m[6] = j; m[7] = n;
	m[8] = c; m[9] = g; m[10] = k; m[11] = o;
	m[12] = d; m[13] = h; m[14] = l; m[15] = p;
}

// matrices
mat4 MatMath::identity_mat4()
{
	return mat4 (
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

mat4 MatMath::zero_mat4() {
	return mat4 (
	0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f
	);
}

mat4 mat4::operator* (const mat4& rhs) {
	mat4 r = MatMath::zero_mat4 ();
	int r_index = 0;
	for (int col = 0; col < 4; col++) {
		for (int row = 0; row < 4; row++) {
			float sum = 0.0f;
			for (int i = 0; i < 4; i++) {
				sum += rhs.m[i + col * 4] * m[row + i * 4];
			}
			r.m[r_index] = sum;
			r_index++;
		}
	}
	return r;
}

// matrix transformations
mat4 MatMath::translate (const mat4& m, const vec3& v) {
	mat4 m_t = MatMath::identity_mat4 ();
	m_t.m[12] = v.x;
	m_t.m[13] = v.y;
	m_t.m[14] = v.z;
	return m_t * m;
}

// dot product
float MatMath::dot(float x1, float y1, float z1, float x2, float y2, float z2)
{
	return x1 * x2 + y1 * y2 + z1 * z2;
}