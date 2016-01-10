#pragma once

#include <stdio.h>
#include <stdint.h>
#include <vector>
#include <SDL.h>

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

#define Pi32 3.14159265359

struct point2D
{
	point2D()
	{
		x = 0;
		y = 0;
	}
	point2D(int posX, int posY)
	{
		x = posX;
		y = posY;
	}

	union
	{
		struct
		{
			int x;
			int y;
		};
		int arr[2];
	};
};

struct vec2
{
	vec2()
	{
		x = 0;
		y = 0;
	}
	vec2(float posX, float posY)
	{
		x = posX;
		y = posY;
	}

	static vec2 zero()
	{
		return vec2(0.f,0.f);
	}

	float x;
	float y;
};

struct dfLine
{
	dfLine()
	{
		a = vec2(0,0);
		b = vec2(0,0);
		width = 1;
	}

	dfLine(float x1, float y1, float x2, float y2)
	{
		a = vec2(x1, y1);
		b = vec2(x2, y2);
		width = 1;
	}

	dfLine(vec2 point1, vec2 point2)
	{
		a = vec2(point1.x, point1.y);
		b = vec2(point2.x, point2.y);
		width = 1;
	}

	vec2 a, b;
	float width;
};

struct vec3
{
	vec3()
	{
		x = 0;
		y = 0;
		z = 0;
	}
	vec3(float posX, float posY, float posZ)
	{
		x = posX;
		y = posY;
		z = posZ;
	}

	static vec3 zero()
	{
		return vec3(0.f,0.f,0.f);
	}

	float x;
	float y;
	float z;
};

struct vec4
{
	vec4()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}
	vec4(float posX, float posY, float posZ, float posW)
	{
		x = posX;
		y = posY;
		z = posZ;
		w = posW;
	}

	static vec4 zero()
	{
		return vec4(0.f,0.f,0.f,0.f);
	}

	float x;
	float y;
	float z;
	float w;
};

struct Circle
{
	Circle()
	{
		center = vec2(0,0);
		r = 0;
	}

	Circle(float x, float y, float radius)
	{
		center = vec2(x,y);
		r = radius;
	}

	Circle(vec2 c, float radius)
	{
		center = vec2(c.x,c.y);
		r = radius;
	}

	vec2 center;
	float r;
};

struct Rect
{
	vec2 pos;
	vec2 size;
	vec2 center;

	union
	{
		struct
		{
			float left;
			float top;
			float width;
			float height;
		};
		float arr[4];
	};
	
	float right;
	float bottom;
};


void dfAssert(bool);

void dfLog(char*);
void dfWarn(char*);
void dfError(char*);

int dfStrLen(char*);
int dfStrLen(const char*);
int dfStrLen(const wchar_t*);

bool dfStrCmp(const char*, const char*);
bool dfStrCmp(std::string, std::string);
bool dfStrCmp(std::vector<char>, const char*);
bool dfStrCmp(std::vector<wchar_t>, const char*);
bool dfStrCmp(const wchar_t*, const wchar_t*);

const char* dfStrCat(const char* a, const char* b);

char* dfSubstr(char* a, int len);

int dfStringToInt(const char* str, int size);
int dfStringToInt(std::vector<char> str);
bool dfStringToBool(const char* str);
bool dfStringToBool(std::vector<char> str);

char* dfVectorToCharStar(std::vector<wchar_t>);

float DotProd(vec2 a, vec2 b);

void UpdateRectMembers(Rect* rect);
void RectSet(vec2 pos, vec2 size, Rect* rect);
void RectSet(float x, float y, float w, float h, Rect* rect);
void RectSetPos(vec2 pos, Rect* rect);
void RectSetPos(float x, float y, Rect* rect);
void RectMove(vec2 pos, Rect* rect);
void RectMove(float x, float y, Rect* rect);
void RectSize(vec2 size, Rect* rect);
void RectSize(float w, float h, Rect* rect);

float dfRand();
float dfRand(float min, float max);
int dfRand(int min, int max);