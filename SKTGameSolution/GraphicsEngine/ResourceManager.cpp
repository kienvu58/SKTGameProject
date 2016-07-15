#include "ResourceManager.h"
#include <iostream>
#include <string>
#include <vector>
#include "HelperFunctions.h"
#include "Camera.h"
#include "Shaders.h"

ResourceManager* ResourceManager::s_Instance = nullptr;

ResourceManager::ResourceManager() : m_mapModels(nullptr),
                                     m_map2DTextures(nullptr),
                                     m_mapCubeTextures(nullptr),
                                     m_mapShaders(nullptr),
                                     m_iNumModel(0),
                                     m_iNum2DTexture(0),
                                     m_iNumCubeTexture(0),
                                     m_iNumShader(0)
{
};

ResourceManager::~ResourceManager()
{
	Clear();
}

ResourceManager* ResourceManager::GetInstance()
{
	if (s_Instance == nullptr)
	{
		s_Instance = new ResourceManager();
	}
	return s_Instance;
}

void ResourceManager::DestroyInstance()
{
	if (s_Instance)
	{
		delete s_Instance;
		s_Instance = nullptr;
	}
}

Model* ResourceManager::GetModelById(int id) const
{
	return GetResourceById<Model>(id, m_mapModels);
}

Texture* ResourceManager::GetTexturelById(int id) const
{
	return GetResourceById<Texture>(id, m_map2DTextures);
}

CubeTexture* ResourceManager::GetCubeTextureById(int id) const
{
	return GetResourceById<CubeTexture>(id, m_mapCubeTextures);
}

Shaders* ResourceManager::GetShaderById(int id) const
{
	return GetResourceById<Shaders>(id, m_mapShaders);
}

void ResourceManager::Init(char* resourcePath)
{
	FILE* pfile = fopen(resourcePath, "r");

	if (!pfile)
	{
		std::cout << "Could not open file " << resourcePath << std::endl;
		return;
	}

	char modelPrefix[100];
	char texturePrefix[100];
	char shaderPrefix[100];

	fscanf(pfile, "MODEL_PREFIX %s\n", modelPrefix);
	fscanf(pfile, "TEXTURE_PREFIX %s\n", texturePrefix);
	fscanf(pfile, "SHADER_PREFIX %s\n", shaderPrefix);

	fscanf(pfile, "\n");
	int i;
	//read models
	m_mapModels = new std::map<int, Model*>();
	fscanf(pfile, "#Models: %d\n", &m_iNumModel);
	for (i = 0; i < m_iNumModel; i++)
	{
		int id;
		char filePath[100];
		char prefix[100];
		char heightMapPath[100];
		char tmpHeightMap[100];
		fscanf(pfile, "ID %d\n", &id);
		fscanf(pfile, "FILE %s\n", filePath);
		fscanf(pfile, "HEIGHT_MAP %s\n", heightMapPath);
		Model* m = new Model();
		if (strcmp("NO", heightMapPath) == 0)
			m->Init(strcat(strcpy(prefix, modelPrefix), filePath), 0);
		else
			m->Init(strcat(strcpy(prefix, modelPrefix), filePath),
			        strcat(strcpy(tmpHeightMap, texturePrefix), heightMapPath));
		m_mapModels->insert(std::pair<int, Model*>(id, m));
	}

	//read 2dTexture
	m_map2DTextures = new std::map<int, Texture*>();
	fscanf(pfile, "#2D Textures: %d\n", &m_iNum2DTexture);
	for (i = 0; i < m_iNum2DTexture; i++)
	{
		int id;
		char filePath[100];
		char prefix[100];
		char type[100];
		fscanf(pfile, "ID %d\n", &id);
		fscanf(pfile, "FILE %s\n", filePath);
		fgets(type, sizeof(type), pfile);
		Texture* t = new Texture();
		t->LoadTGAFile(strcat(strcpy(prefix, texturePrefix), filePath));
		m_map2DTextures->insert(std::pair<int, Texture*>(id, t));
	}

	//read cube textures
	fscanf(pfile, "\n");
	m_mapCubeTextures = new std::map<int, CubeTexture*>();
	fscanf(pfile, "#Cube Textures: %d\n", &m_iNumCubeTexture);
	for (i = 0; i < m_iNumCubeTexture; i++)
	{
		int id;
		char filePath[100];
		char prefix[100];
		char type[100];
		fscanf(pfile, "ID %d\n", &id);
		fscanf(pfile, "FILE %s\n", filePath);
		fgets(type, sizeof(type), pfile);
		std::vector<char*> paths;
		strcat(strcpy(prefix, texturePrefix), filePath);
		char tmp[6][100];
		paths.push_back(strcat(strcpy(tmp[0], prefix), "right.tga"));
		paths.push_back(strcat(strcpy(tmp[1], prefix), "left.tga"));
		paths.push_back(strcat(strcpy(tmp[2], prefix), "bottom.tga"));
		paths.push_back(strcat(strcpy(tmp[3], prefix), "top.tga"));
		paths.push_back(strcat(strcpy(tmp[4], prefix), "back.tga"));
		paths.push_back(strcat(strcpy(tmp[5], prefix), "front.tga"));
		CubeTexture* c = new CubeTexture();
		c->LoadTGAFiles(paths);
		m_mapCubeTextures->insert(std::pair<int, CubeTexture*>(id, c));
	}

	//read shaders
	fscanf(pfile, "\n");
	m_mapShaders = new std::map<int, Shaders*>();
	fscanf(pfile, "#Shader: %d\n", &m_iNumShader);
	for (i = 0; i < m_iNumShader; i++)
	{
		int id;
		char vsPath[100];
		char fsPath[100];
		char prefix[100];
		fscanf(pfile, "ID %d\n", &id);
		fscanf(pfile, "VS %s\n", vsPath);
		fscanf(pfile, "FS %s\n", fsPath);
		Shaders* s = new Shaders();
		char tmp[100];
		strcpy(tmp, shaderPrefix);
		strcat(tmp, fsPath);
		s->Init(strcat(strcpy(prefix, shaderPrefix), vsPath),
		        tmp);
		int numStates;
		fscanf(pfile, "STATES %d\n", &numStates);
		for (int j = 0; j < numStates; j++)
		{
			char type[100];
			fscanf(pfile, "STATE %s\n", type);
			if (strcmp(type, "CULLING") == 0)
			{
				s->states.push_back(ShaderState::CULLING);
			}
			if (strcmp(type, "DEPTH_TEST") == 0)
			{
				s->states.push_back(ShaderState::DEPTH_TEST);
			}
			if (strcmp(type, "ALPHA") == 0)
			{
				s->states.push_back(ShaderState::ALPHA);
			}
		}
		m_mapShaders->insert(std::pair<int, Shaders*>(id, s));
	}

	fclose(pfile);
}

void ResourceManager::Clear()
{
	ClearMap<Model>(m_mapModels);
	ClearMap<Texture>(m_map2DTextures);
	ClearMap<CubeTexture>(m_mapCubeTextures);
	ClearMap<Shaders>(m_mapShaders);
}

void ResourceManager::InsertModel(Model* model)
{
	m_mapModels->insert(std::pair<int, Model*>(m_iNumModel, model));
	m_iNumModel++;
}
