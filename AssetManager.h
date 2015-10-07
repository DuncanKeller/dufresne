#pragma once
#include "gamesystem.h"
#include <Windows.h>
#include <map>

#include <stack>
#include <iostream>
#include <string>
#include <vector>
#include <tchar.h>
#include "glew.h"

#include "dfBasic.h"

struct dfFile
{
	char* contents;
	int size;
};

struct UniformInfo
{
	std::vector<char> name;
	dfBasicType type;
};

struct ShaderInfo
{
	dfFile shaderFile;
	std::vector<UniformInfo> uniforms;
	int vertFragType;
};

class AssetManager :
	public GameSystem
{
public:
	AssetManager(void);
	virtual ~AssetManager(void);

	void InitAssetPool(int size);
	bool LoadLoosePackage(std::wstring);

	dfFile GetAsset(const wchar_t*);
	
	bool CalculateLoosePackageSize(std::wstring );
	uint32 PlatformGetFileSize(const wchar_t*);
	bool LoadFileIntoPool(const wchar_t *filename, char* loadLocation);
	std::vector<wchar_t> GetFileExtension(const wchar_t* fullFilename);

	// shader
	void InitShader(char* fullShaderSrc, ShaderInfo &shader);

	// debug
	void DebugTestWritePoolToFile();

	std::vector<ShaderInfo> shaders;
	std::map<const wchar_t*, ShaderInfo> shaderMap;
	char* assetPool;
	std::map<const wchar_t*, dfFile> assetMap;
	int poolsize;

};

