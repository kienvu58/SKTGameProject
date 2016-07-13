#pragma once
#include "Model.h"
#include <map>
#include "Texture.h"
#include "CubeTexture.h"
#include "Shaders.h"

class ResourceManager
{
private:
	std::map<int, Model*> *m_mapModels;
	std::map<int, Texture*> *m_map2DTextures;
	std::map<int, CubeTexture*> *m_mapCubeTextures;
	std::map<int, Shaders*> *m_mapShaders;

	ResourceManager():m_iNumModel(0),
					  m_iNum2DTexture(0),
					  m_iNumCubeTexture(0),
				      m_iNumShader(0),
					  m_mapModels(0),
			          m_map2DTextures(0),
			          m_mapCubeTextures(0),
					  m_mapShaders(0)
	{};
	static ResourceManager *instance;
public:
	static ResourceManager* GetInstance();
	~ResourceManager();
	int m_iNumModel;
	int m_iNum2DTexture;
	int m_iNumCubeTexture;
	int m_iNumShader;

	Model* GetModelById(int id);
	Texture* GetTexturelById(int id);
	CubeTexture* GetCubeTextureById(int id);
	Shaders* GetShaderById(int id);

	void Init(char *resourcePath);
	void Clear();
};

