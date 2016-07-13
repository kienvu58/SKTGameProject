#pragma once
#include "../Utilities/utilities.h" 
#include "Model.h"
#include <map>
#include "Texture.h"
#include "CubeTexture.h"
#include "Shaders.h"
#include "Object.h"
#include "Math.h"

class SceneManager
{
private:
	static SceneManager* instance;
	int m_iNumObjects;
	std::map<int, Object*> *m_mapObjects;
	SceneManager(): m_iNumObjects(0), 
		            m_mapObjects(nullptr)
				    {};
public:
	~SceneManager();
	static SceneManager* GetInstance();
	void Init(char *filePath);
	void Draw();

	void Clear();
	void Update(float deltaTime);
	void ProcessInput( float deltaTime);

	Object* GetObjectById(int id);
};

