#include "STDUNC.h"

void dfAssert(bool condition)
{
	// TODO replace with something reasonable
	if(!condition)
	{
		int farts = 0;
		int fart = 12 / farts;
	}
}

void dfLog(char *msg)
{
	// TODO more logging. Console output?
	printf(msg);
}

int dfStrLen(char* str)
{
	int l = 0;
	while(true)
	{
		char current = str[l];
		if(str[l] == '\0')
		{
			return l;
		}
		l++;
	}
}

int dfStrLen(const char* str)
{
	int l = 0;
	while(true)
	{
		char current = str[l];
		if(str[l] == '\0')
		{
			return l;
		}
		l++;
	}
}

int dfStrLen(const wchar_t* str)
{
	int l = 0;
	while(true)
	{
		char current = str[l];
		if(str[l] == '\0')
		{
			return l;
		}
		l++;
	}
}

bool dfStrCmp(char* str1, char* str2)
{
	int l1 = dfStrLen(str1);
	int l2 = dfStrLen(str2);

	if(l1 != l2)
		return false;

	for(int i = 0; i < l1; i++)
	{
		if(str1[i] != str2[i])
			return false;
	}

	return true;
}

bool dfStrCmp(std::vector<char> str1, const char* str2)
{
	int l1 = str1.size();
	int l2 = dfStrLen(str2);

	if(l1 != l2)
		return false;

	for(int i = 0; i < l1; i++)
	{
		if(str1[i] != str2[i])
			return false;
	}

	return true;
}

bool dfStrCmp(std::vector<wchar_t> str1, const char* str2)
{
	int l1 = str1.size();
	int l2 = dfStrLen(str2);

	if(l1 != l2)
		return false;

	for(int i = 0; i < l1; i++)
	{
		if(str1[i] != str2[i])
			return false;
	}

	return true;
}

char* dfVectorToCharStar(std::vector<wchar_t> vec)
{
	char* newStr = (char*)malloc(sizeof(char) * vec.size());
	for(int i = 0; i < vec.size(); i++)
	{
		newStr[i] = vec[i];
	}
	return newStr;
}


void UpdateRectMembers(Rect &rect)
{
	rect.width = rect.size.x;
	rect.height = rect.size.y;
	rect.top = rect.pos.y;
	rect.bottom = rect.pos.y + rect.height;
	rect.left = rect.pos.x;
	rect.right = rect.pos.x + rect.width;
	rect.center = vec2(
		rect.pos.x + rect.width,
		rect.pos.y + rect.height);
}

void RectSet(vec2 pos, vec2 size, Rect &rect)
{
	rect.pos = pos;
	rect.size = size;
	UpdateRectMembers(rect);
}

void RectSet(float x, float y, float w, float h, Rect &rect)
{
	rect.pos = vec2(x, y);
	rect.size = vec2(w, h);
	UpdateRectMembers(rect);
}

void RectSetPos(vec2 pos, Rect &rect)
{
	rect.pos = pos;
	UpdateRectMembers(rect);
}

void RectSetPos(float x, float y, Rect &rect)
{
	rect.pos = vec2(x, y);
	UpdateRectMembers(rect);
}

void RectMove(vec2 pos, Rect &rect)
{
	rect.pos.x += pos.x;
	rect.pos.y += pos.y;
	UpdateRectMembers(rect);
}

void RectMove(float x, float y, Rect &rect)
{
	rect.pos.x +=x;
	rect.pos.y += y;
	UpdateRectMembers(rect);
}

void RectSize(vec2 size, Rect &rect)
{
	rect.size = size;
	UpdateRectMembers(rect);
}

void RectSize(float w, float h, Rect &rect)
{
	rect.size = vec2(w, h);
	UpdateRectMembers(rect);
}
