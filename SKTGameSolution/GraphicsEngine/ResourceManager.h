#pragma once
#include "Model.h"
#include <map>
#include "Shaders.h"
#include "SpriteSheet.h"

class ResourceManager
{
public:
	static ResourceManager* GetInstance();
	static void DestroyInstance();
	Model* GetModelById(int id) const;
	SpriteSheet* GetSpriteSheetById(int id) const;
	Shaders* GetShadersById(int id) const;
	void Init(const char *resourcePath);
	~ResourceManager();
private:
	std::map<int, Model*> m_mapModels;
	std::map<int, SpriteSheet*> m_mapSpiteSheets;
	std::map<int, Shaders*> m_mapShaders;
	static ResourceManager *s_Instance;
	ResourceManager();
};


#define ResourceMgr ResourceManager::GetInstance()

