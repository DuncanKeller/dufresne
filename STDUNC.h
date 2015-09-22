#pragma once

#include <stdio.h>
#include <stdint.h>

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

#define Pi32 3.14159265359

struct Rectangle
{
	float left;
	float right;
	float top;
	float bottom;
};

struct Vec2
{
	float x;
	float y;
};

struct Vec3
{
	float x;
	float y;
	float z;
};

void dfAssert(bool);

void dfLog(char*);

int dfStrLen(char*);

bool dfStrCmp(char*, char*);