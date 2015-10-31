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
		set.tilePxWidth = tilesetObj.getChild("tilewidth").asInt();
		set.tilePxHeight = tilesetObj.getChild("tileheight").asInt();
		set.numTiles = tilesetObj.getChild("tilecount").asInt();
		set.name = tilesetObj.getChild("name").asString();		
		int imgWidth =  tilesetObj.getChild("imagewidth").asInt();
		int imgHeight =  tilesetObj.getChild("imageheight").asInt();
		
		std::string filename = tilesetObj.getChild("image").asString();
		const char* cstrfilename = filename.c_str();
		const wchar_t* wcharfilename = (wchar_t*)filename.c_str();
		TextureInfo texture = assMan.GetTexture(L"fart\\testtiles.png"); // todo obviouslly not hardcode path...
		set.texture = texture;

		set.numTilesWidth = ((imgWidth - set.margin * 2) + set.spacing) / (set.tilePxWidth + set.spacing);
		set.numTileHeight = ((imgHeight - set.margin * 2) + set.spacing) / (set.tilePxHeight + set.spacing);

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
				TileInfo t;
				t.tilemapGUID = tileData.getChild(tileIndex).asInt() - 1;
				if(t.tilemapGUID != -1)
				{
					t.xIndex = tileIndex % widthInTiles;
					t.yIndex = tileIndex / widthInTiles;
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
				
					t.tilesetXIndex = t.tilemapGUID % tilesets[t.tilesetIndex].numTilesWidth;
					t.tilesetYIndex = t.tilemapGUID / tilesets[t.tilesetIndex].numTilesWidth;

					layer.tiles.push_back(t);
				}
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
	for(int layerIndex = 0; layerIndex < tileLayers.size(); layerIndex++)
	{
		TileLayer layer = tileLayers[layerIndex];
		for(int tileIndex = 0; tileIndex < layer.tiles.size(); tileIndex++)
		{
			TileInfo t = layer.tiles[tileIndex];
			tiles.push_back(new dfTile());
			dfTile* tile = tiles[tiles.size() - 1];

			Tileset set = tilesets[t.tilesetIndex];
			// todo: use a configurable size for the tiles, not just pixel size of tile
			tile->tf.SetPos(t.xIndex * set.tilePxWidth, t.yIndex * set.tilePxHeight);
			RectSize(set.tilePxWidth, set.tilePxHeight, tile->render.renderRect);
			tile->render.InitSprite(set.texture, set.numTileHeight, set.numTilesWidth, set.margin, set.spacing);
			tile->render.SetAtlasLocation(t.tilesetXIndex, t.tilesetYIndex);
			tile->render.renderInfo.depth = layerIndex + 10; // todo more robust layering for tiles
		}
	}
}