#include "STDUNC.h"

void dfAssert(bool condition)
{
	if(!condition)
	{
		int farts = 0;
		int fart = 12 / farts;
	}
}

void dfLog(char *msg)
{
	SDL_Log(msg);
}

void dfWarn(char *msg)
{
	SDL_Log(msg);
}

void dfError(char *msg)
{
	SDL_Log(msg);
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

bool dfStrCmp(const char* str1, const char* str2)
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

bool dfStrCmp(const wchar_t* str1, const wchar_t* str2)
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

bool dfStrCmp(std::string str1, std::string str2)
{
	int l1 = str1.length();
	int l2 = str2.length();

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


const char* dfStrCat(const char* a, const char* b)
{
	int len1 = 0;
	int len2 = 0;
    const char * first = a;
	const char * second = b;

    while (*first++) 
		len1++;
    while (*second++) 
		len2++;

    char *result = new char[len1 + len2];

    for (int i = 0; i < len1; i++) 
		result[i] = a[i];
    for (int i = len1; i < len1 + len2; i++) 
		result[i] = b[i - len1];

    result[len1+len2] = '\0';
    return result;
}

char* dfSubstr(char* a, int len)
{
	char* newStr = (char*)malloc(len+1);
	for(int i = 0; i < len; i++)
	{
		newStr[i] = a[i];
	}
	newStr[len] = '\0';
	return newStr;
}

int dfStringToInt(const char* str, int size)
{
	int result = 0;
	int place = 1;

	for(int i = size - 1; i >= 0; i--)
	{
		char c = str[i];
		int num = c - '0';
		if(num < 0 || num > 9)
			dfAssert(false); // parsed something bad

		result += num * place;
		place *= 10;
	}
	return result;
}

int dfStringToInt(std::vector<char> str)
{
	int result = 0;
	int place = 1;
	
	for(int i = str.size() - 1; i >= 0; i--)
	{
		char c = str[i];
		int num = c - '0';
		if(num < 0 || num > 9)
			dfAssert(false); // parsed something bad

		result += num * place;
		place *= 10;
	}
	return result;
}

bool dfStringToBool(const char* str)
{
	char c = str[0];
	int num = c - '0';
	if(num != 0 && num != 1)
		dfAssert(false); // parsed something bad

	return num == 1;
}

bool dfStringToBool(std::vector<char> str)
{
	char c = str[0];
	int num = c - '0';
	if(num != 0 && num != 1)
		dfAssert(false); // parsed something bad

	return num == 1;
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

float DotProd(vec2 a, vec2 b)
{
	return a.x * b.x + a.y * b.y;
}

void UpdateRectMembers(Rect *rect)
{
	rect->width = rect->size.x;
	rect->height = rect->size.y;
	rect->top = rect->pos.y;
	rect->bottom = rect->pos.y + rect->height;
	rect->left = rect->pos.x;
	rect->right = rect->pos.x + rect->width;
	rect->center = vec2(
		rect->pos.x + rect->width / 2.f,
		rect->pos.y + rect->height / 2.f);
}

void RectSet(vec2 pos, vec2 size, Rect *rect)
{
	rect->pos = pos;
	rect->size = size;
	UpdateRectMembers(rect);
}

void RectSet(float x, float y, float w, float h, Rect *rect)
{
	rect->pos = vec2(x, y);
	rect->size = vec2(w, h);
	UpdateRectMembers(rect);
}

void RectSetPos(vec2 pos, Rect *rect)
{
	rect->pos = pos;
	UpdateRectMembers(rect);
}

void RectSetPos(float x, float y, Rect *rect)
{
	rect->pos = vec2(x, y);
	UpdateRectMembers(rect);
}

void RectMove(vec2 pos, Rect *rect)
{
	rect->pos.x += pos.x;
	rect->pos.y += pos.y;
	UpdateRectMembers(rect);
}

void RectMove(float x, float y, Rect *rect)
{
	rect->pos.x +=x;
	rect->pos.y += y;
	UpdateRectMembers(rect);
}

void RectSize(vec2 size, Rect *rect)
{
	rect->size = size;
	UpdateRectMembers(rect);
}

void RectSize(float w, float h, Rect *rect)
{
	rect->size = vec2(w, h);
	UpdateRectMembers(rect);
}

float dfRand()
{
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

float dfRand(float min, float max)
{
	return min + (static_cast <float> (rand()) / ( static_cast <float> (RAND_MAX / max - min)));
}

int dfRand(int min, int max)
{
	return min + (rand() % (max - min));
}