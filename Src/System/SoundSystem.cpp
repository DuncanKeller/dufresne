#include "SoundSystem.h"

SoundSystem sfxMan;

SoundSystem::SoundSystem(void)
{
}


SoundSystem::~SoundSystem(void)
{
}


void SoundSystem::Init()
{

}

void SoundSystem::Update()
{

}
	
void SoundSystem::PlaySound(const wchar_t* name)
{
	PlaySound(name, 1.f);
}

void SoundSystem::PlaySound(const wchar_t* name, float volume)
{
	SoundInfo sfxInfo = assMan.GetSound(name);
	sfxInfo.chunk->volume = (Uint8)(volume * 128);
	Mix_PlayChannel(-1, sfxInfo.chunk, 0);
}