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

	LoadTilemap(L"fart\\tilemap1.json");
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

		set.hasCollisionAtlas = false;

		// tileset properties
		JsonObject props = tilesetObj.getChild("properties");
		for(int pIndex = 0; pIndex < props.numChildren(); pIndex++)
		{
			// todo store property as correct type (int or bool) if it can parse it
			JsonKeyValue propObj = props.getObjectChild(pIndex);
			TileProperty objProp;
			objProp.name = propObj.key;
			objProp.value = propObj.value.asString();
			set.properites.push_back(objProp);
		}

		tilesets.push_back(set);
	}

	// layers
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

			// tile layers
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

			// ojbect layers
			JsonObject objectLayerData = layerObj.getChild("objects");
			for(int objIndex = 0; objIndex < objectLayerData.numChildren(); objIndex++)
			{
				JsonObject objectData = objectLayerData.getChild(objIndex);
				ObjectInfo obj;
				obj.layerIndex = layerIndex;
				obj.system = this;

				obj.xPosition = objectData.getChild("x").asFloat();
				obj.yPosition = objectData.getChild("y").asFloat();
				obj.rotation = objectData.getChild("rotation").asFloat();
				

				obj.tilemapGUID = objectData.getChild("gid").asInt() - 1;
				if(obj.tilemapGUID != -1) // uses an image on the tilemap
				{
					// figure out the cooresponding tileset
					int tileCounter = 0;
					for(int tsIndex = 0; tsIndex < tilesets.size(); tsIndex++)
					{
						tileCounter += tilesets[tsIndex].numTiles;
						if(obj.tilemapGUID < tileCounter)
						{
							obj.tilesetIndex = tsIndex;
							break;
						}
					}
				
					obj.tilesetXIndex = obj.tilemapGUID % tilesets[obj.tilesetIndex].numTilesWidth;
					obj.tilesetYIndex = obj.tilemapGUID / tilesets[obj.tilesetIndex].numTilesWidth;
					obj.widthPx = tilesets[obj.tilesetIndex].tilePxWidth;
					obj.heightPx = tilesets[obj.tilesetIndex].tilePxHeight;
				}
				else // no tilemap image
				{
					obj.tilesetIndex = -1;
					obj.widthPx = objectData.getChild("width").asFloat();
					obj.heightPx = objectData.getChild("height").asFloat();
				}

				// object properties
				JsonObject props = objectData.getChild("properties");
				for(int pIndex = 0; pIndex < props.numChildren(); pIndex++)
				{
					// todo store property as correct type (int or bool) if it can parse it
					JsonKeyValue propObj = props.getObjectChild(pIndex);
					TileProperty objProp;
					objProp.name = propObj.key;
					objProp.value = propObj.value.asString();
					obj.properites.push_back(objProp);
				}
				layer.objects.push_back(obj);
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

void TileMap::InterpretProperty(Tileset* tileset, const wchar_t* name, const wchar_t* value)
{
	if(dfStrCmp(name, L"collision-atlas"))
	{
		ParseCollisionAtlas(tileset, value);
	}
}

void TileMap::ParseCollisionAtlas(Tileset* tileset, const wchar_t* filename)
{
	JsonObject jsonObj = JsonObject();
	std::string str = assMan.GetTextFile((const wchar_t*)filename);

	// todo weird bug, not having some spaces at the end tries to parse garbage... whyyyy...
	// workaround is to use the string content, but the file size, which has the correct cap.
	if(!jsonObj.parse(str.c_str(), assMan.GetAsset((const wchar_t*)filename).size, &jsonObj))
	{
		dfAssert(false);
		// json load failed...
	}

	JsonObject collisionTiles = jsonObj.getChild("tiles");
	for(int i = 0; i < collisionTiles.numChildren(); i++)
	{
		std::vector<CollisionVolumeInfo> volumes;

		JsonObject cTile = collisionTiles.getChild(i);
		JsonObject volumesObj = cTile.getChild("volumes");
		for(int volumeIndex = 0; volumeIndex < volumesObj.numChildren(); volumeIndex++)
		{
			CollisionVolumeInfo cvolumeInfo;
			JsonObject volume = volumesObj.getChild(volumeIndex);
			JsonObject verts = volume.getChild("verts");
			for(int vertIndex = 0; vertIndex< verts.numChildren(); vertIndex++)
			{
				JsonObject vert = verts.getChild(vertIndex);
				int x = vert.getChild("x").asInt();
				int y = vert.getChild("y").asInt();
				cvolumeInfo.coords.push_back(vec2(x, y));
			}
			cvolumeInfo.square = volume.getChild("rectangle").asBool();
			volumes.push_back(cvolumeInfo);
		}
		
		tileset->collisionAtlas.push_back(volumes);
	}

	if(collisionTiles.numChildren() > 0)
	{
		tileset->hasCollisionAtlas = true;
	}
}

void TileMap::GenerateMapSystem()
{
	// handle custom properties for tilesets
	for(int i = 0; i < tilesets.size(); i++)
	{
		for(int pIndex = 0; pIndex < tilesets[i].properites.size(); pIndex++)
		{
			std::wstring nameStr = std::wstring(tilesets[i].properites[pIndex].name.begin(), tilesets[i].properites[pIndex].name.end());
			std::wstring valStr = std::wstring(tilesets[i].properites[pIndex].value.begin(), tilesets[i].properites[pIndex].value.end());
			InterpretProperty(&tilesets[i], nameStr.c_str(), valStr.c_str());
		}
	}

	for(int layerIndex = 0; layerIndex < tileLayers.size(); layerIndex++)
	{
		TileLayer layer = tileLayers[layerIndex];
		for(int tileIndex = 0; tileIndex < layer.tiles.size(); tileIndex++)
		{
			TileInfo t = layer.tiles[tileIndex];
			
			dfTile* tile = sceneMan.CreateSceneObject<dfTile>();
			tiles.push_back(tile);

			Tileset set = tilesets[t.tilesetIndex];
			// todo: use a configurable size for the tiles, not just pixel size of tile
			tile->tf.SetPos(t.xIndex * set.tilePxWidth, t.yIndex * set.tilePxHeight);
			RectSize(set.tilePxWidth, set.tilePxHeight, tile->render.renderRect);
			tile->render.InitSprite(set.texture, set.numTileHeight, set.numTilesWidth, set.margin, set.spacing);
			tile->render.SetAtlasLocation(t.tilesetXIndex, t.tilesetYIndex);
			tile->render.renderInfo.depth = layerIndex + 10; // todo more robust layering for tiles

			if(set.hasCollisionAtlas)
			{
				for(int cIndex = 0; cIndex < set.collisionAtlas[t.tilesetIndex].size(); cIndex++)
				{
					// todo support non-square
					CollisionVolumeInfo volume = set.collisionAtlas[t.tilesetIndex][cIndex];
					if(volume.square)
					{
						BoxCollider* bc = new BoxCollider();
						Rect* r = new Rect();
						RectSet(volume.coords[0].x + tile->tf.rectangle.pos.x, 
							volume.coords[0].y + tile->tf.rectangle.pos.y,
							volume.coords[3].x - volume.coords[0].x,
							volume.coords[3].y - volume.coords[0].y, r);
						bc->collisionRect = r;
						bc->SetEnabled(true);
						tile->RegisterComponent(bc);
					}
				}
			}

			// read all custom properties from tiles
			for(int i = 0; i < t.properites.size(); i++)
			{
				tile->InterpretProperty(t.properites[i].name.c_str(), t.properites[i].value.c_str());
			}
			for(int i = 0; i < layer.properites.size(); i++)
			{
				tile->InterpretProperty(layer.properites[i].name.c_str(), layer.properites[i].value.c_str());
			}
		}

		for(int objIndex = 0; objIndex < layer.objects.size(); objIndex++)
		{
			ObjectInfo obj = layer.objects[objIndex];

			dfTile* tile = sceneMan.CreateSceneObject<dfTile>();
			tiles.push_back(tile);

			Tileset set = tilesets[obj.tilesetIndex];
			tile->tf.SetPos(obj.xPosition, obj.yPosition); // todo configurable size that matches tilemap size above
			RectSize(obj.widthPx, obj.heightPx, tile->render.renderRect);

			if(obj.tilemapGUID >= 0)
			{
				tile->render.InitSprite(set.texture, set.numTileHeight, set.numTilesWidth, set.margin, set.spacing);
				tile->render.SetAtlasLocation(obj.tilesetXIndex, obj.tilesetYIndex);
			}
			else
			{
				tile->render.SetTexture(set.texture);
			}
			tile->render.renderInfo.depth = layerIndex + 10; // todo more robust layering for tiles

			// read all custom properties from tiles
			for(int i = 0; i < obj.properites.size(); i++)
			{
				tile->InterpretProperty(obj.properites[i].name.c_str(), obj.properites[i].value.c_str());
			}
			for(int i = 0; i < layer.properites.size(); i++)
			{
				tile->InterpretProperty(layer.properites[i].name.c_str(), layer.properites[i].value.c_str());
			}
		}
	}
}