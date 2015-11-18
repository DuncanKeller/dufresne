#pragma once
#include "Entity.h"
#include <Windows.h>
#include <map>

#include <stack>
#include <iostream>
#include <string>
#include <vector>
#include <tchar.h>
#include "glew.h"

#include "SDL.h"
#include "SDL_image.h"

#include "dfBasic.h"

class AssetManager :
	public Entity
{
public:
	AssetManager(void);
	virtual ~AssetManager(void);

	void InitAssetPool(int size);
	bool LoadLoosePackage(std::wstring);
	
	dfFile GetAsset(const wchar_t*);
	ShaderInfo GetShader(const wchar_t*);
	TextureInfo GetTexture(const wchar_t*);
	std::string GetTextFile(const wchar_t*);
	
	bool CalculateLoosePackageSize(std::wstring );
	uint32 PlatformGetFileSize(const wchar_t*);
	bool LoadFileIntoPool(const wchar_t *filename, char* loadLocation);
	std::vector<wchar_t> GetFileExtension(const wchar_t* fullFilename);

	// init asset types
	void InitShader(char* fullShaderSrc, ShaderInfo &shader);
	void InitTexture(TextureInfo &texture);

	// debug
	void DebugTestWritePoolToFile();

	// todo this filename hash is pretty half baked, need a better solution, or at least a better hash
	// todo apply same treatment of hash to the shader pool.
	long GetHash(const wchar_t* filename);
	std::vector<ShaderInfo> shaders;
	std::map<long, ShaderInfo> shaderMap;
	std::vector<TextureInfo> textures;
	std::map<long, TextureInfo> textureMap;
	std::vector<std::string> textFiles;
	std::map<long, std::string> textFileMap;
	char* assetPool;
	std::map<long, dfFile> assetMap;
	int poolsize;

};

extern AssetManager assMan; // yep I'm naming this variable assMan, just try and stop me!