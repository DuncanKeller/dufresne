#pragma once
#include "DFComponent.h"
#include "Transform.h"
#include "Renderer.h"


const int CHAR_LIMIT = 255;

class bmpTextEntity :
	public dfComponent
{
public:
	bmpTextEntity(void);
	bmpTextEntity(std::wstring text);
	bmpTextEntity(std::wstring text, const wchar_t* fontPath, int columns, int rows);
	virtual ~bmpTextEntity(void);

	virtual void Init();
	virtual void Update();

	void GenGlyphs();
	void SetText(std::wstring text);
	void SetColor(vec4 color);
	void SetCharacterWidths(const wchar_t* assetPath);
	void SetSize(int newSize);
	
	int textLength;
	point2D characterSize;
	int modifiedSize;
	Renderer glyphs[CHAR_LIMIT];
	Rect glyphRects[CHAR_LIMIT];
	int layer;

	int rows;
	int columns;

	std::map<int, int> characterWidths;
	dfBitmapFont font;

	Transform* tf;

private:
	std::wstring text;

	bool monospace;

};

