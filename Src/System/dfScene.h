#pragma once
#include "../Entity/Entity.h"
#include <vector>
#include "../Components/BoxCollider.h"
#include "../Core/DFCman.h"

static const int MAX_OBJS_PER_SCENE = 99999;

class dfScene :
	public Entity
{
public:
	dfScene(void);
	virtual ~dfScene(void);

	virtual void Init();
	virtual void Update();

	void (*setupFunc)();
	virtual void SetupScene();

	std::string name;
	int currentNum;
	std::vector<int> freeSpots;
	Entity* sceneObjects[MAX_OBJS_PER_SCENE];

	Entity* GetEntityByIndex(int i);
	void RemoveSceneObject(Entity* sceneObj);

	void DoCollision();

	void RemoveAllSceneObjects();
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

		dfError("shoot, added too many objects to the scene :c");
		dfAssert(false);
		return 0;
	}

};

