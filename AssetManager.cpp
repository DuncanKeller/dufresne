#include "AssetManager.h"


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

dfFile AssetManager::GetAsset(const wchar_t* key)
{
	return assetMap[key];
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
				assetMap[filename] = newAsset;
				
				loadLocation += filesizeOUT;
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