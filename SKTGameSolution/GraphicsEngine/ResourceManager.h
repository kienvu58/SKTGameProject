#pragma once
#include "Model.h"
#include <map>
#include "Texture.h"
#include "CubeTexture.h"
#include "Shaders.h"

class ResourceManager
{
public:
	static ResourceManager* GetInstance();
	static void DestroyInstance();
	Model* GetModelById(int id) const;
	Texture* GetTexturelById(int id) const;
	CubeTexture* GetCubeTextureById(int id) const;
	Shaders* GetShaderById(int id) const;
	void Init(char *resourcePath);
	void Clear();
	void InsertModel(Model *model);
	~ResourceManager();
private:
	std::map<int, Model*> *m_mapModels;
	std::map<int, Texture*> *m_map2DTextures;
	std::map<int, CubeTexture*> *m_mapCubeTextures;
	std::map<int, Shaders*> *m_mapShaders;
	int m_iNumModel;
	int m_iNum2DTexture;
	int m_iNumCubeTexture;
	int m_iNumShader;
	static ResourceManager *s_Instance;
	ResourceManager();
};


#define ResourceMgr ResourceManager::GetInstance()

