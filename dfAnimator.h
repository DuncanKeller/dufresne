#pragma once
#include "dfcomponent.h"
#include "Renderer.h"
#include "AssetManager.h"
#include "tinyjsonp.h"
#include <vector>

struct AnimationInfo
{
	std::string name;
	bool looping;
	float framesPerSecond;
	std::vector<int> frames;
	int loopbackFrame;
};

class dfAnimator :
	public dfComponent
{
public:
	dfAnimator(wchar_t* animFilename);
	virtual ~dfAnimator(void);
	virtual void Init();
	virtual void Update();

	Renderer* render;

	std::vector<AnimationInfo> anims;
	int currentAnimIndex;
	int currentFrame;
	bool playing;
	float timer;

	void LoadAnimJSON(wchar_t* animFilename);
	void Play();
	void Play(std::string animName);
	void Pause();
	void SetFrame(int frame);
};

