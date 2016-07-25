#pragma once
#include <map>
#include "GraphicalObject.h"
#include "Camera.h"

class SceneManager
{
public:
	static SceneManager* GetInstance();
	static void DestroyInstance();
	void Init(char* filePath);
	void Draw();

	void Clear();
	void Update(float deltaTime);

	GraphicalObject* GetObjectById(int id);
	~SceneManager();
private:
	static SceneManager* s_Instance;
	int m_iNumObjects;
	Camera* m_pCamera;
	std::map<int, GraphicalObject*> *m_mapObjects;

	SceneManager();
};


#define SceneMgr SceneManager::GetInstance()
