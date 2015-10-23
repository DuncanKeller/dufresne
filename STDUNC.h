#pragma once

#include <stdio.h>
#include <stdint.h>
#include <vector>

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

	float x;
	float y;
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

	float x;
	float y;
	float z;
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

int dfStrLen(char*);
int dfStrLen(const char*);
int dfStrLen(const wchar_t*);

bool dfStrCmp(char*, char*);
bool dfStrCmp(std::vector<char>, const char*);
bool dfStrCmp(std::vector<wchar_t>, const char*);

const char* dfStrCat(const char* a, const char* b);

int dfStringToInt(char* str, int size);
int dfStringToInt(std::vector<char> str);

char* dfVectorToCharStar(std::vector<wchar_t>);

void UpdateRectMembers(Rect &rect);
void RectSet(vec2 pos, vec2 size, Rect &rect);
void RectSet(float x, float y, float w, float h, Rect &rect);
void RectSetPos(vec2 pos, Rect &rect);
void RectSetPos(float x, float y, Rect &rect);
void RectMove(vec2 pos, Rect &rect);
void RectMove(float x, float y, Rect &rect);
void RectSize(vec2 size, Rect &rect);
void RectSize(float w, float h, Rect &rect);
// todo more rect funcs: overlapping, other stuff. check xna for all its useful stuff