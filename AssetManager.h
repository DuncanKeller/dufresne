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

#include "SDL.h"
#include "SDL_image.h"

#include "dfBasic.h"

// todo const char* goes out of scope and gets gronked
// could be fixed if we go to a real string class, so too lazy to fix right now
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

// todo move the ____info structs outside of assetmanager? Into dfBasic?
struct ShaderInfo
{
	dfFile shaderFile;
	std::vector<UniformInfo> uniforms;
	int vertFragType;
};

struct TextureInfo
{
	dfFile file;
	char* name;
	std::vector<wchar_t> filetype;
	int width;
	int height;
	unsigned int glTexture;
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
	ShaderInfo GetShader(const wchar_t*);
	TextureInfo GetTexture(const wchar_t*);
	
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
	double GetHash(const wchar_t* filename);
	std::vector<ShaderInfo> shaders;
	std::map<double, ShaderInfo> shaderMap;
	std::vector<TextureInfo> textures;
	std::map<double, TextureInfo> textureMap;
	char* assetPool;
	std::map<double, dfFile> assetMap;
	int poolsize;

};

extern AssetManager assMan; // yep I'm naming this variable assMan, just try and stop me!