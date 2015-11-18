#pragma once
#include "Entity.h"
#include "dfScene.h"
#include "RenderSystem.h"

class SceneManager :
	public Entity
{
public:
	SceneManager(void);
	virtual ~SceneManager(void);

	virtual void Init();
	virtual void Update();
	
	void LoadScene(dfScene* scene);
	void LoadScene(std::string name);
	// void LoadSceneAdditive(dfScene scene); todo implement

	dfScene* currentScene;
	std::vector<dfScene> sceneList;

	RenderSystem renderer;

	void RemoveSceneObject(Entity* system);

	template<class T> T* CreateSceneObject()
	{
		if(currentScene != NULL)
		{
			return currentScene->CreateSceneObject<T>();
		}
		else
		{
			dfLog("NO SCENE TO ADD OBJECT TO"); // todo make dfLogError
		}
	}
};

extern SceneManager sceneMan;