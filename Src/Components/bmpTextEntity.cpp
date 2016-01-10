#include "bmpTextEntity.h"
#include "../Entity/Entity.h"

bmpTextEntity::bmpTextEntity(void)
{
	bmpTextEntity(L"");
}

bmpTextEntity::bmpTextEntity(std::wstring text)
{
	bmpTextEntity(text, L"fart\\defaultFont.png", 16, 16);
}

bmpTextEntity::bmpTextEntity(std::wstring text, const wchar_t* fontPath, int columns, int rows)
{
	font.texture = assMan.GetTexture(fontPath);

	layer = 0;
	monospace = true;
	bmpTextEntity::text = text;
	textLength = 0;
	modifiedSize = 0;

	characterSize.x = font.texture.width / columns;
	characterSize.y = font.texture.height / rows;
	
	bmpTextEntity::columns = columns;
	bmpTextEntity::rows = rows;
}

bmpTextEntity::~bmpTextEntity(void)
{
}

void bmpTextEntity::Init()
{
	tf = entity->GetComponent<Transform>();
	SetText(text);
}

void bmpTextEntity::Update()
{

}

void bmpTextEntity::GenGlyphs()
{
	int lineNumber = 0;
	int xPositionIndex = 0;

	for(int i = 0; i < text.length(); i++)
	{
		if(text[i] == '\n' || text[i] == '\r\n')
		{
			lineNumber++;
		}
		else
		{
			glyphs[i].renderRect = &glyphRects[i];
			glyphs[i].InitSprite(font.texture, rows, columns, 0, 0);
			glyphs[i].SetAtlasLocation(asciiTable[text[i]]);
			Renderer::SetSpecialUniforms(glyphs[i].renderInfo, glyphs[i].spriteInfo, &glyphs[i]);
			
			int sizeX = characterSize.x;
			int sizeY = characterSize.y;
			float ratioDiff = 1.f;
			if(modifiedSize > 0)
			{
				ratioDiff = (float)modifiedSize / sizeY;
				sizeX = (int)(sizeX * ratioDiff);
				sizeY = (int)(sizeY * ratioDiff);
			}

			if(characterWidths.size() > 0)
				xPositionIndex += (int)(characterWidths[asciiTable[text[i]]] * ratioDiff);
			else
				xPositionIndex += sizeX;

			RectSet(
				tf->rectangle.left + xPositionIndex, 
				tf->rectangle.top + (sizeY * lineNumber),
				sizeX, sizeY, 
				&glyphRects[i]);
			glyphs[i].renderInfo.depth = layer;
			
			for(int j = 0; j < glyphs[i].renderInfo.uniforms.size(); j++)
			{
				if(dfStrCmp("rect", glyphs[i].renderInfo.uniforms[j].name))
				{
					glyphs[i].renderInfo.uniforms[j].valueRect =  &glyphRects[i];
					break;
				}
			}
		}
	}
}

void bmpTextEntity::SetColor(vec4 color)
{
	for(int i = 0; i < textLength; i++)
	{
		glyphs[i].renderInfo.color = color;
	}
	GenGlyphs();
}

void bmpTextEntity::SetCharacterWidths(const wchar_t* path)
{
	dfFile file = assMan.GetAsset(path);
	for(int i = 0; i < file.size / 2; i++)
	{
		int size = (int)file.contents[i * 2];
		characterWidths[i] = size;
	}
	GenGlyphs();
}

void bmpTextEntity::SetText(std::wstring text)
{
	bmpTextEntity::text = text;
	textLength = text.length();
	GenGlyphs();
}

void bmpTextEntity::SetSize(int size)
{
	modifiedSize = size;
	GenGlyphs();
}