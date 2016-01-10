#pragma once
#include "..\Entity\GameSystem.h"
#include "..\..\SDL2_mixer-2.0.0\SDL_mixer.h"
#include "AssetManager.h"
class SoundSystem :
	public GameSystem
{
public:
	SoundSystem(void);
	virtual ~SoundSystem(void);

	virtual void Init();
	virtual void Update();
	
	void PlaySound(const wchar_t* name);
	void PlaySound(const wchar_t* name, float volume);
};

extern SoundSystem sfxMan;