#include "bmpTextEntity.h"


bmpTextEntity::bmpTextEntity(void)
{
	bmpTextEntity(L"", L"default font path");
}

bmpTextEntity::bmpTextEntity(std::wstring text)
{
	bmpTextEntity(text, L"default font path");
}

bmpTextEntity::bmpTextEntity(std::wstring text, const wchar_t* fontPath)
{
	RegisterComponent(&tf);

	monospace = true;
	bmpTextEntity::text = text;
}

bmpTextEntity::~bmpTextEntity(void)
{
}

void bmpTextEntity::Init()
{

}

void bmpTextEntity::Update()
{

}

void bmpTextEntity::GenGlyphs()
{
	for(int i = 0; i < text.length(); i++)
	{
		
	}
}

void bmpTextEntity::SetText(std::wstring text)
{
	bmpTextEntity::text = text;
	GenGlyphs();
}