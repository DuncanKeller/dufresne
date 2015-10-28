#include "TileMap.h"


TileMap::TileMap(void)
{
}


TileMap::~TileMap(void)
{
}


void TileMap::Init()
{
	GameSystem::Init();

	LoadTilemap(L"fart\\testmap.json");
	GenerateMapSystem();
}

void TileMap::Update()
{
	GameSystem::Update();
}


void TileMap::LoadTilemap(wchar_t* mapname)
{
	JsonObject jsonObj = JsonObject();
	std::string str = assMan.GetTextFile((const wchar_t*)mapname);

	// todo weird bug, not having some spaces at the end tries to parse garbage... whyyyy...
	// workaround is to use the string content, but the file size, which has the correct cap.
	if(!jsonObj.parse(str.c_str(), assMan.GetAsset((const wchar_t*)mapname).size, &jsonObj))
	{
		dfAssert(false);
		// json load failed...
	}

	// globals
	int widthInTiles = jsonObj.getChild("width").asInt();
	int heightInTiles = jsonObj.getChild("height").asInt();

	
	// tilesets
	JsonObject tilesetsObj = jsonObj.getChild("tilesets");
	for(int index = 0; index < tilesetsObj.numChildren(); index++)
	{
		JsonObject tilesetObj = tilesetsObj.getChild(index);
		Tileset set;
		set.margin = tilesetObj.getChild("margin").asInt();
		set.spacing = tilesetObj.getChild("spacing").asInt();
		set.tileWidth = tilesetObj.getChild("tilewidth").asInt();
		set.tileHeight = tilesetObj.getChild("tileheight").asInt();
		set.numTiles = tilesetObj.getChild("tilecount").asInt();
		set.name = tilesetObj.getChild("name").asString();

		tilesets.push_back(set);
	}

	// layers
	// todo object layers parsing
	JsonObject layers = jsonObj.getChild("layers");
	for(int layerIndex = 0; layerIndex < layers.numChildren(); layerIndex++)
	{
		JsonObject layerObj = layers.getChild(layerIndex);
		TileLayer layer;
		
		bool visible = layerObj.getChild("visible").asBool();
		if(visible)
		{
			layer.xOffset = layerObj.getChild("x").asInt();
			layer.yOffset = layerObj.getChild("y").asInt();
			layer.widthInTiles = layerObj.getChild("width").asInt();
			layer.heightInTiles = layerObj.getChild("height").asInt();
			layer.name = layerObj.getChild("name").asString();
			layer.opacity = layerObj.getChild("opacity").asFloat();

			JsonObject tileData = layerObj.getChild("data");
			for(int tileIndex = 0; tileIndex < tileData.numChildren(); tileIndex++)
			{
				Tile t;
				t.tilemapGUID = tileData.getChild(tileIndex).asInt() - 1;
				t.xIndex = t.tilemapGUID % widthInTiles;
				t.yIndex = t.tilemapGUID / widthInTiles;
				t.layerIndex = layerIndex;
				t.system = this;
				
				// figure out the cooresponding tileset
				int tileCounter = 0;
				for(int tsIndex = 0; tsIndex < tilesets.size(); tsIndex++)
				{
					tileCounter += tilesets[tsIndex].numTiles;
					if(t.tilemapGUID < tileCounter)
					{
						t.tilesetIndex = tsIndex;
						break;
					}
				}

				layer.tiles.push_back(t);
			}

			// layer properties
			JsonObject props = layerObj.getChild("properties");
			for(int pIndex = 0; pIndex < props.numChildren(); pIndex++)
			{
				// todo store property as correct type (int or bool) if it can parse it
				JsonKeyValue propObj = props.getObjectChild(pIndex);
				TileProperty tileProp;
				tileProp.name = propObj.key;
				tileProp.value = propObj.value.asString();
				layer.properites.push_back(tileProp);
			}

			tileLayers.push_back(layer);
		}
	}

}

void TileMap::GenerateMapSystem()
{

}