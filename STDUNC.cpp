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