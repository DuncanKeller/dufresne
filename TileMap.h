#pragma once
#include "Entity.h"
#include "dfBasic.h"
#include "AssetManager.h"
#include "tinyjsonp.h"
#include "dfTile.h"
#include "SceneManager.h"
#include "STDUNC.h"

struct TileProperty
{
	std::string name;
	std::string value;
};

struct CollisionVolumeInfo
{
	bool square;
	std::vector<vec2> coords;
};

struct Tileset
{
	TextureInfo texture;
	std::string name;
	int margin;
	int spacing;
	int tilePxWidth;
	int tilePxHeight;
	int numTilesWidth;
	int numTileHeight;
	int numTiles;
	std::vector<TileProperty> properites;
	bool hasCollisionAtlas;
	std::vector<std::vector<CollisionVolumeInfo>> collisionAtlas;
};

struct TileInfo
{
	Entity *system;
	int xIndex;
	int yIndex;
	int hIndex;
	int layerIndex;
	int tilesetIndex;
	int tilemapGUID; // index of tile picture
	int tilesetXIndex;
	int tilesetYIndex;
	std::vector<TileProperty> properites;
};

struct ObjectInfo
{
	Entity *system;
	float xPosition;
	float yPosition;
	float layerIndex;
	int tilesetIndex;
	int tilemapGUID; // index of tile picture
	float rotation;
	int tilesetXIndex;
	int tilesetYIndex;
	std::vector<TileProperty> properites;
	float widthPx;
	float heightPx;
};

struct TileLayer
{
	std::string name;
	std::vector<TileInfo> tiles;
	std::vector<ObjectInfo> objects;
	int widthInTiles;
	int heightInTiles;
	int xOffset;
	int yOffset;
	int index;
	float opacity;
	std::vector<TileProperty> properites;
};


class TileMap :
	public Entity
{
public:
	TileMap(std::wstring tilemapFilename);
	virtual ~TileMap(void);
	virtual void Init();
	virtual void Update();
	std::wstring tilemapFilename;

	void LoadTilemap(wchar_t* mapname);
	void GenerateMapSystem();
	void InterpretProperty(Tileset* tileset, const wchar_t* name, const wchar_t* value);
	void ParseCollisionAtlas(Tileset* tileset, const wchar_t* value);
	vec2 GetScreenCoordFromIndex(int x, int y, int h);

	std::vector<Tileset> tilesets;
	std::vector<TileLayer> tileLayers;

	std::vector<dfTile*> tiles;

	bool isometric;
	int pxWidth;
	int pxHeight;
};

