#pragma once
#include "../Entity/GameSystem.h"
#include "dfScene.h"
#include "RenderSystem.h"

class SceneManager :
	public GameSystem
{
public:
	SceneManager(void);
	virtual ~SceneManager(void);

	virtual void Init();
	virtual void Update();

	dfScene* CreateScene(std::string name);
	
	void LoadScene(dfScene* scene);
	void LoadScene(std::string name);
	// void LoadSceneAdditive(dfScene scene); todo implement
	void UnloadScene(dfScene* scene);

	dfScene* currentScene;
	std::vector<dfScene*> sceneList;

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