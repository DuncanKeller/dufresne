#include "dfAnimator.h"
#include "Entity.h"

// todo: constructor that takes some struct so you can manually define animations 
// without a json file. Will be faster in cases where there are very few anims, or even just one
dfAnimator::dfAnimator(wchar_t* animFilename)
{
	currentAnimIndex = 0;
	currentFrame = 0;
	playing = true;
	timer = 0.f;

	LoadAnimJSON(animFilename);
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

	timer += 0.05; // todo repalce with dt

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

	// todo weird bug, not having some spaces at the end tries to parse garbage... whyyyy...
	// workaround is to use the string content, but the file size, which has the correct cap.
	if(!jsonObj.parse(str.c_str(), assMan.GetAsset((const wchar_t*)animFilename).size, &jsonObj))
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