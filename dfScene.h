#pragma once
#include "gamesystem.h"
#include <vector>
#include "BoxCollider.h"

static const int MAX_OBJS_PER_SCENE = 99999;

class dfScene :
	public GameSystem
{
public:
	dfScene(void);
	virtual ~dfScene(void);

	virtual void Init();
	virtual void Update();


	std::string name;
	int currentNum;
	std::vector<int> freeSpots;
	GameSystem* sceneObjects[MAX_OBJS_PER_SCENE];

	GameSystem* GetGameSystemByIndex(int i);
	void RemoveSceneObject(GameSystem* sceneObj);

	void DoCollision();

	template<class T> T* CreateSceneObject()
	{
		int useIndex = -1;
		if(freeSpots.size() > 0)
		{
			useIndex = freeSpots[freeSpots.size() - 1];
			freeSpots.pop_back();
		}
		else if(currentNum < MAX_OBJS_PER_SCENE - 1)
		{
			useIndex = currentNum;
			currentNum++;
		}

		if(useIndex != -1)
		{
			T* newObj = new T();
			sceneObjects[useIndex] = newObj;
			return newObj;
		}

		dfAssert(false); // added too many objects to scene, at max number. todo assert message / log
		return 0;
	}

};

