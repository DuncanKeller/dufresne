#include "AssetManager.h"

AssetManager assMan;

AssetManager::AssetManager(void)
{
	assetPool = NULL;
	poolsize = 0;
}


AssetManager::~AssetManager(void)
{
}

void AssetManager::InitAssetPool(int size)
{
	if(assetPool != NULL)
		free(assetPool);

	assetPool = (char*)malloc(size);
	poolsize = size;
}

double AssetManager::GetHash(const wchar_t* filename)
{
	double hash = 0;
	for(int i = 0; i < dfStrLen(filename); i++)
	{
		hash += i * filename[i];
	}
	return hash;
}

dfFile AssetManager::GetAsset(const wchar_t* key)
{
	return assetMap[GetHash(key)];
}

void AssetManager::InitShader(char* fullShaderSrc, ShaderInfo &shader)
{
	// TODO array support
	const char* matchingVert = "!vert";
	int matchingVertIndex = 0;
	const char* matchingFrag = "!frag";
	int matchingFragIndex = 0;
	const char* matchingString = "uniform";
	int strLen = dfStrLen(matchingString);
	int matchingIndex = 0;
	int numMatches = 0;

	bool gettingLine = false;
	dfBasicType lastType;
	bool doneReadingType = false;
	std::vector<char> currentType;

	// todo cache strlen, shaders can be looong
	for(int i = 0; i < dfStrLen(fullShaderSrc); i++)
	{
		// vert or frag
		if(fullShaderSrc[i] == matchingVert[matchingVertIndex])
		{
			matchingVertIndex++;
			if(matchingVertIndex == 5) // length of "!vert" or "!frag"
			{
				shader.vertFragType = GL_VERTEX_SHADER;
			}
		}
		if(fullShaderSrc[i] == matchingFrag[matchingFragIndex])
		{
			matchingFragIndex++;
			if(matchingFragIndex == 5) // length of "!vert" or "!frag"
			{
				shader.vertFragType = GL_FRAGMENT_SHADER; 
			}
		}

		if(fullShaderSrc[i] == matchingString[matchingIndex])
		{
			matchingIndex++;
			if(matchingIndex == strLen)
			{
				// match found, add line to list
				gettingLine = true;
				matchingIndex = 0;
				UniformInfo newInfo;			
				shader.uniforms.push_back(newInfo);
				continue;
			}
		}
		if(gettingLine)
		{

			if(!doneReadingType) // need to get shader type
			{
				if(fullShaderSrc[i] != ' ') // reading shader type
				{
					currentType.push_back(fullShaderSrc[i]);
				}
				else if(currentType.size() > 0) // done reading type
				{
					shader.uniforms[numMatches].type = dfGetTypeFromString(currentType);
					lastType = shader.uniforms[numMatches].type;

					doneReadingType = true;
					currentType.clear();
				}
			}
			else  // read in shader name
			{
				if(fullShaderSrc[i] != ' ') // reading shader type
				{
					if(fullShaderSrc[i] == ',') // new name, not end of line
					{
						shader.uniforms[numMatches].type = lastType;
						numMatches++; 
						UniformInfo newInfo;
						shader.uniforms.push_back(newInfo);
					}
					else if(fullShaderSrc[i] == ';')  // new name, end of line
					{
						shader.uniforms[numMatches].type = lastType;
						numMatches++; 

						lastType = DF_null;
						doneReadingType = false;
						gettingLine = false;
					}
					else
					{
						shader.uniforms[numMatches].name.push_back(fullShaderSrc[i]);
					}
				}
			}
		}	
	}
}

std::vector<wchar_t>  AssetManager::GetFileExtension(const wchar_t* fullFilename)
{
	int fullLength = dfStrLen(fullFilename);
	int length = 0;
	std::vector<wchar_t> result;
	for(int i = fullLength; i > 0; i--)
	{
		if(fullFilename[i] == '.')
		{
			for(int j = i+1; j < fullLength; j++)
			{
				result.push_back(fullFilename[j]);
			}
		}
	}

	return result;
}

bool AssetManager::LoadLoosePackage(std::wstring path)
{
	HANDLE hFind = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATA ffd;
    std::stack<std::wstring> directories;

    directories.push(path);

	char* assetPointer = assetPool;

    while (!directories.empty()) 
	{
        path = directories.top();
        directories.pop();
		
        hFind = FindFirstFile((path + L"*").c_str(), &ffd);
        if (hFind == INVALID_HANDLE_VALUE)
		{
            return false;
        } 

        do {
            if (wcscmp(ffd.cFileName, L".") != 0 && 
                wcscmp(ffd.cFileName, L"..") != 0) 
			{
                if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
				{
                    directories.push(path + ffd.cFileName  + L"\\");
                }
                else 
				{
					std::wstring filepath = path + ffd.cFileName;
					LoadFileIntoPool(filepath.c_str(), assetPointer);

                }
            }
        } while (FindNextFile(hFind, &ffd) != 0);

        if (GetLastError() != ERROR_NO_MORE_FILES)
		{
            FindClose(hFind);
            return false;
        }

        FindClose(hFind);
        hFind = INVALID_HANDLE_VALUE;
    }

    return true;
}

bool AssetManager::CalculateLoosePackageSize(std::wstring path) 
{
    HANDLE hFind = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATA ffd;
    std::stack<std::wstring> directories;

    directories.push(path);

	int assetPackageSize = 0;

    while (!directories.empty()) 
	{
        path = directories.top();
        directories.pop();

        hFind = FindFirstFile((path + L"*").c_str(), &ffd);
        if (hFind == INVALID_HANDLE_VALUE)
		{
            return false;
        } 

        do {
            if (wcscmp(ffd.cFileName, L".") != 0 && 
                wcscmp(ffd.cFileName, L"..") != 0) 
			{
                if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
				{
                    directories.push(path + ffd.cFileName + L"\\" );
                }
                else 
				{
					std::wstring filepath = path + ffd.cFileName;
					uint32 filesize = PlatformGetFileSize(filepath.c_str());				
					assetPackageSize += filesize;
                }
            }
        } while (FindNextFile(hFind, &ffd) != 0);

        if (GetLastError() != ERROR_NO_MORE_FILES)
		{
            FindClose(hFind);
            return false;
        }

        FindClose(hFind);
        hFind = INVALID_HANDLE_VALUE;
    }

	InitAssetPool(assetPackageSize);

    return true;
}

bool AssetManager::LoadFileIntoPool(const wchar_t *filename, char* loadLocation)
{
	HANDLE fileHandle = CreateFile(filename, GENERIC_READ, 
		FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL);
	if(fileHandle != INVALID_HANDLE_VALUE)
	{
		LARGE_INTEGER fileSize;
		if(GetFileSizeEx(fileHandle, &fileSize))
		{
			// ReadFile() can't handle 64 bit values, so just assert it is below that
			dfAssert(fileSize.QuadPart <= 0xFFFFFFFF);

			DWORD bytesRead = 0;
			if(ReadFile(fileHandle, (LPVOID)loadLocation, (uint32)fileSize.QuadPart, &bytesRead, 0) &&
				fileSize.QuadPart == bytesRead)
			{
				uint32 filesizeOUT = fileSize.QuadPart;

				dfFile newAsset;
				newAsset.size = filesizeOUT;
				newAsset.contents = loadLocation;
				
				assetMap[GetHash(filename)] = newAsset;
				
				loadLocation += filesizeOUT;

				// check file type for extra stuff
				std::vector<wchar_t> fileType = GetFileExtension(filename);
				if(dfStrCmp(fileType, "glsl"))
				{
					ShaderInfo shader;
					shader.vertFragType = 0;
					shader.shaderFile = newAsset;

					InitShader(newAsset.contents, shader);

					shaders.push_back(shader);
					shaderMap[(wchar_t*)filename] = shader;
				}
			}
			else
			{
				return false;
			}
			
		}
		CloseHandle(fileHandle);
	}
	return true;
}

uint32 AssetManager::PlatformGetFileSize(const wchar_t *filename)
{
	uint32 size = 0;
	HANDLE fileHandle = CreateFile(filename, GENERIC_READ, 
		FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL);
	if(fileHandle != INVALID_HANDLE_VALUE)
	{
		LARGE_INTEGER fileSize;
		if(GetFileSizeEx(fileHandle, &fileSize))
		{
			// ReadFile() can't handle 64 bit values, so just assert it is below that
			dfAssert(fileSize.QuadPart <= 0xFFFFFFFF);
			size = fileSize.QuadPart;
		}
		CloseHandle(fileHandle);
	}
	return size;
}

void AssetManager::DebugTestWritePoolToFile()
{
	char* filename = "testassetpool.fart";
	bool success = false;
	HANDLE fileHandle = CreateFile((LPCWSTR)filename, GENERIC_WRITE, 
		NULL, NULL, CREATE_ALWAYS, NULL, NULL);
		
	if(fileHandle != INVALID_HANDLE_VALUE)
	{
		DWORD bytesWritten;
		if(WriteFile(fileHandle, assetPool, poolsize, &bytesWritten, NULL))
		{
			success = bytesWritten == poolsize;
		}
		
		CloseHandle(fileHandle);
	}
}