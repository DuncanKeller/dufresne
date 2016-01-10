#include "dfAnimator.h"
#include "../Entity/Entity.h"

dfAnimator::dfAnimator(wchar_t* animFilename)
{
	currentAnimIndex = 0;
	currentFrame = 0;
	playing = true;
	timer = 0.f;

	LoadAnimJSON(animFilename);
}

dfAnimator::dfAnimator(std::string name, float spd, int frames)
{
	AnimationInfo info;
	for(int i = 0; i < frames; i++)
		info.frames.push_back(i);
	info.framesPerSecond = spd;
	info.loopbackFrame = 0;
	info.looping = true;
	info.name = name;
}

dfAnimator::dfAnimator(std::vector<AnimationInfo> animationList)
{
	currentAnimIndex = 0;
	currentFrame = 0;
	playing = true;
	timer = 0.f;

	anims = animationList;
}

dfAnimator::~dfAnimator(void)
{
}

void dfAnimator::Init()
{
	dfComponent::Init();

	render = entity->GetComponent<Renderer>();
}

void dfAnimator::Update()
{
	dfComponent::Update();

	timer += dfDeltaTime;

	if(playing)
	{
		if(timer > 1.f / anims[currentAnimIndex].framesPerSecond)
		{
			timer = 0.f;
			currentFrame++;
			if(currentFrame > anims[currentAnimIndex].frames[anims[currentAnimIndex].frames.size() - 1])
				currentFrame = anims[currentAnimIndex].frames[0];

			SetFrame(currentFrame);
		}
	}
}

void dfAnimator::SetFrame(int n)
{
	render->SetAtlasLocation(n);
}

void dfAnimator::Play()
{
	playing = true;
}

void dfAnimator::Play(std::string animName)
{
	for(int i = 0; i < anims.size(); i++)
	{
		if(dfStrCmp(animName.c_str(), anims[i].name.c_str()) && currentAnimIndex != i)
		{
			currentAnimIndex = i;
			currentFrame = anims[i].frames[0];
			Play();
			SetFrame(currentFrame);
		}
	}
}

void dfAnimator::Pause()
{
	playing = false;
}

void dfAnimator::LoadAnimJSON(wchar_t* animFilename)
{
	JsonObject jsonObj = JsonObject();
	std::string str = assMan.GetTextFile((const wchar_t*)animFilename);

	if(!jsonObj.parse(str.c_str(), str.length(), &jsonObj))
	{
		// json load failed...
		dfAssert(false);
	}

	//animations
	JsonObject animListObj = jsonObj.getChild("animations");
	for(int i = 0; i < animListObj.numChildren(); i++)
	{
		AnimationInfo animInfo;
		JsonKeyValue animObj = animListObj.getObjectChild(i);
		animInfo.name = animObj.key;

		animInfo.framesPerSecond = animObj.value.getChild("fps").asFloat();
		std::string frameInfoStr = animObj.value.getChild("frames").asString();
		
		animInfo.looping = true;

		std::string currentNumStr = "";
		int lastNum = -1;

		for(int i = 0; i < frameInfoStr.length(); i++)
		{
			char c = frameInfoStr[i];
			if(c == '-' || c == ':')
			{
				int currentNum = dfStringToInt(currentNumStr.c_str(), currentNumStr.length());
				currentNumStr = "";

				if(lastNum != -1)
				{
					if(currentNum > lastNum)
						for(int index = lastNum; index < currentNum + 1; index++)
							animInfo.frames.push_back(index);
					else
						for(int index = currentNum; index >= lastNum; index--)
							animInfo.frames.push_back(index);
				}

				lastNum = currentNum;

			}
			else if(c ==',')
			{
				int currentNum = dfStringToInt(currentNumStr.c_str(), currentNumStr.length());
				currentNumStr = "";
				
				if(lastNum != -1)
				{
					if(currentNum > lastNum)
						for(int index = lastNum; index < currentNum + 1; index++)
							animInfo.frames.push_back(index);
					else
						for(int index = currentNum; index >= lastNum; index--)
							animInfo.frames.push_back(index);
				}
				else
				{
					animInfo.frames.push_back(currentNum);
				}

				lastNum = -1;
			}
			else if(c =='0' || c =='1' || c =='2' || c =='3' || c =='4' 
				 || c =='5' || c =='6' || c =='7' || c =='8' || c =='9')
			{
				currentNumStr += c;
			}
		}

		// do it a final time
		int currentNum = dfStringToInt(currentNumStr.c_str(), currentNumStr.length());
		currentNumStr = "";
				
		if(lastNum != -1)
		{
			if(currentNum > lastNum)
				for(int index = lastNum; index < currentNum + 1; index++)
					animInfo.frames.push_back(index);
			else
				for(int index = currentNum; index >= lastNum; index--)
					animInfo.frames.push_back(index);
		}
		else
		{
			animInfo.frames.push_back(currentNum);
		}
		
		if(animInfo.frames.size() > 0)
			animInfo.loopbackFrame = animInfo.frames[0];

		anims.push_back(animInfo);
	}


}