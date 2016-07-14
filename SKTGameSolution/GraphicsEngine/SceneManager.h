#pragma once
#include <map>
#include "Object.h"
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

	Object* GetObjectById(int id);
	~SceneManager();
private:
	static SceneManager* s_Instance;
	int m_iNumObjects;
	Camera* m_pCamera;
	std::map<int, Object*> *m_mapObjects;

	SceneManager();
};


#define SceneMgr SceneManager::GetInstance()
