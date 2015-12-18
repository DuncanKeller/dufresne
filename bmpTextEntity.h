#pragma once
#include "entity.h"
#include "Transform.h"
#include "Renderer.h"
class bmpTextEntity :
	public Entity
{
public:
	bmpTextEntity(void);
	bmpTextEntity(std::wstring text);
	bmpTextEntity(std::wstring text, const wchar_t* fontPath);
	virtual ~bmpTextEntity(void);

	virtual void Init();
	virtual void Update();

	void GenGlyphs();
	void SetText(std::wstring text);
	
	std::vector<Renderer> glyphs;

	Transform tf;

private:
	std::wstring text;

	bool monospace;

};

