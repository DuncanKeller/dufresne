#pragma once
#include "gamesystem.h"
#include "dfBasic.h"
#include "AssetManager.h"
#include "tinyjsonp.h"
#include "dfTile.h"
#include "SceneManager.h"

struct TileProperty
{
	std::string name;
	std::string value;
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
};

struct TileInfo
{
	GameSystem *system;
	int xIndex;
	int yIndex;
	int layerIndex;
	int tilesetIndex;
	int tilemapGUID; // index of tile picture
	int tilesetXIndex;
	int tilesetYIndex;
	std::vector<TileProperty> properites;
};

struct TileLayer
{
	std::string name;
	std::vector<TileInfo> tiles;
	int widthInTiles;
	int heightInTiles;
	int xOffset;
	int yOffset;
	int index;
	float opacity;
	std::vector<TileProperty> properites;
};


class TileMap :
	public GameSystem
{
public:
	TileMap(void);
	virtual ~TileMap(void);
	virtual void Init();
	virtual void Update();

	void LoadTilemap(wchar_t* mapname);
	void GenerateMapSystem();
	
	std::vector<Tileset> tilesets;
	std::vector<TileLayer> tileLayers;

	std::vector<dfTile*> tiles;
};

