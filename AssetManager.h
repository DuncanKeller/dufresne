#pragma once
#include "gamesystem.h"
#include <Windows.h>
#include <map>

#include <stack>
#include <iostream>
#include <string>
#include <vector>
#include <tchar.h>

struct dfFile
{
	char* contents;
	int size;
};

class AssetManager :
	public GameSystem
{
public:
	AssetManager(void);
	virtual ~AssetManager(void);

	void InitAssetPool(int size);
	bool LoadLoosePackage(std::wstring );

	dfFile GetAsset(const wchar_t*);
	
	bool CalculateLoosePackageSize(std::wstring );
	uint32 PlatformGetFileSize(const wchar_t*);
	bool LoadFileIntoPool(const wchar_t *filename, char* loadLocation);

	void DebugTestWritePoolToFile();

	char* assetPool;
	std::map<const wchar_t*, dfFile> assetMap;
	int poolsize;

};

