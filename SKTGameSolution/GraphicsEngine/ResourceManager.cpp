#include <json.hpp>
#include "ResourceManager.h"
#include <fstream>
#include "HelperFunctions.h"
#include "Camera.h"
#include "Shaders.h"

#define MAX_CHAR_LENGTH 100

ResourceManager::ResourceManager()
{
};

ResourceManager::~ResourceManager()
{
	ClearMap<Shaders>(m_mapShaders);
	ClearMap<Model>(m_mapModels);
	ClearMap<SpriteSheet>(m_mapSpiteSheets);
}

Model* ResourceManager::GetModelById(int id) const
{
	return GetResourceById<Model>(id, m_mapModels);
}

SpriteSheet* ResourceManager::GetSpriteSheetById(int id) const
{
	return GetResourceById<SpriteSheet>(id, m_mapSpiteSheets);
}

Shaders* ResourceManager::GetShadersById(int id) const
{
	return GetResourceById<Shaders>(id, m_mapShaders);
}

void ResourceManager::Init(const char* resourcePath)
{
	std::ifstream fin(resourcePath);
	nlohmann::json data(fin);
	fin.close();

	// init models
	for (auto it : data["models"])
	{
		int id, modelW, modelH, spriteW, spriteH, textureW, textureH;
		id = it["id"].get<int>();
		modelW = it["modelW"].get<int>();
		modelH = it["modelH"].get<int>();
		spriteW = it["spriteW"].get<int>();
		spriteH = it["spriteH"].get<int>();
		textureW = it["textureW"].get<int>();
		textureH = it["textureH"].get<int>();

		Model* model = new Model(id);
		model->Init(modelW, modelH, spriteW, spriteH, textureW, textureH);
		m_mapModels.insert(std::pair<int, Model*>(id, model));
	}

	// init spriteSheets
	for (auto it : data["spriteSheets"])
	{
		int id, nRows, nColumns;
		id = it["id"].get<int>();
		nRows = it["nRows"].get<int>();
		nColumns = it["nColumns"].get<int>();
		auto path = it["path"].get<std::string>();

		SpriteSheet* spriteSheet = new SpriteSheet(id, nRows, nColumns);
		spriteSheet->LoadTGAFile(path.c_str());
		m_mapSpiteSheets.insert(std::pair<int, SpriteSheet*>(id, spriteSheet));
	}

	// init shaders
	for (auto it : data["shaders"])
	{
		int id;
		id = it["id"].get<int>();
		auto vsPath = it["vsPath"].get<std::string>();
		auto fsPath = it["fsPath"].get<std::string>();
		Shaders* shader = new Shaders();
		shader->Init(const_cast<char*>(vsPath.c_str()), const_cast<char*>(fsPath.c_str()));
		m_mapShaders.insert(std::pair<int, Shaders*>(id, shader));
	}
}

//	FILE* pfile = fopen(resourcePath, "r");
//
//	if (!pfile)
//	{
//		std::cout << "Could not open file " << resourcePath << std::endl;
//		return;
//	}
//
//	char modelPrefix[MAX_CHAR_LENGTH];
//	char texturePrefix[MAX_CHAR_LENGTH];
//	char shaderPrefix[MAX_CHAR_LENGTH];
//
//	fscanf(pfile, "MODEL_PREFIX %s\n", modelPrefix);
//	fscanf(pfile, "TEXTURE_PREFIX %s\n", texturePrefix);
//	fscanf(pfile, "SHADER_PREFIX %s\n", shaderPrefix);
//
//	fscanf(pfile, "\n");
//	int i;
//	//read models
//	m_mapModels = new std::map<int, Model*>();
//	fscanf(pfile, "#Models: %d\n", &m_iNumModel);
//	for (i = 0; i < m_iNumModel; i++)
//	{
//		int id;
//		char filePath[MAX_CHAR_LENGTH];
//		char prefix[MAX_CHAR_LENGTH];
//		char heightMapPath[MAX_CHAR_LENGTH];
//		char tmpHeightMap[MAX_CHAR_LENGTH];
//		fscanf(pfile, "ID %d\n", &id);
//		fscanf(pfile, "FILE %s\n", filePath);
//		fscanf(pfile, "HEIGHT_MAP %s\n", heightMapPath);
//		Model* m = new Model();
//		if (strcmp("NO", heightMapPath) == 0)
//			m->Init(strcat(strcpy(prefix, modelPrefix), filePath), 0);
//		else
//			m->Init(strcat(strcpy(prefix, modelPrefix), filePath),
//			        strcat(strcpy(tmpHeightMap, texturePrefix), heightMapPath));
//		m_mapModels->insert(std::pair<int, Model*>(id, m));
//	}
//
//	//read 2dTexture
//	m_map2DTextures = new std::map<int, Texture*>();
//	fscanf(pfile, "#2D Textures: %d\n", &m_iNum2DTexture);
//	for (i = 0; i < m_iNum2DTexture; i++)
//	{
//		int id;
//		char filePath[MAX_CHAR_LENGTH];
//		char prefix[MAX_CHAR_LENGTH];
//		char type[MAX_CHAR_LENGTH];
//		fscanf(pfile, "ID %d\n", &id);
//		fscanf(pfile, "FILE %s\n", filePath);
//		fgets(type, sizeof(type), pfile);
//		Texture* t = new Texture();
//		t->LoadTGAFile(strcat(strcpy(prefix, texturePrefix), filePath));
//		m_map2DTextures->insert(std::pair<int, Texture*>(id, t));
//	}
//
//	//read cube textures
//	fscanf(pfile, "\n");
//	m_mapCubeTextures = new std::map<int, CubeTexture*>();
//	fscanf(pfile, "#Cube Textures: %d\n", &m_iNumCubeTexture);
//	for (i = 0; i < m_iNumCubeTexture; i++)
//	{
//		int id;
//		char filePath[MAX_CHAR_LENGTH];
//		char prefix[MAX_CHAR_LENGTH];
//		char type[MAX_CHAR_LENGTH];
//		fscanf(pfile, "ID %d\n", &id);
//		fscanf(pfile, "FILE %s\n", filePath);
//		fgets(type, sizeof(type), pfile);
//		std::vector<char*> paths;
//		strcat(strcpy(prefix, texturePrefix), filePath);
//		char tmp[6][MAX_CHAR_LENGTH];
//		paths.push_back(strcat(strcpy(tmp[0], prefix), "right.tga"));
//		paths.push_back(strcat(strcpy(tmp[1], prefix), "left.tga"));
//		paths.push_back(strcat(strcpy(tmp[2], prefix), "bottom.tga"));
//		paths.push_back(strcat(strcpy(tmp[3], prefix), "top.tga"));
//		paths.push_back(strcat(strcpy(tmp[4], prefix), "back.tga"));
//		paths.push_back(strcat(strcpy(tmp[5], prefix), "front.tga"));
//		CubeTexture* c = new CubeTexture();
//		c->LoadTGAFiles(paths);
//		m_mapCubeTextures->insert(std::pair<int, CubeTexture*>(id, c));
//	}
//
//	//read shaders
//	fscanf(pfile, "\n");
//	m_mapShaders = new std::map<int, Shaders*>();
//	fscanf(pfile, "#Shader: %d\n", &m_iNumShader);
//	for (i = 0; i < m_iNumShader; i++)
//	{
//		int id;
//		char vsPath[MAX_CHAR_LENGTH];
//		char fsPath[MAX_CHAR_LENGTH];
//		char prefix[MAX_CHAR_LENGTH];
//		fscanf(pfile, "ID %d\n", &id);
//		fscanf(pfile, "VS %s\n", vsPath);
//		fscanf(pfile, "FS %s\n", fsPath);
//		Shaders* s = new Shaders();
//		char tmp[MAX_CHAR_LENGTH];
//		strcpy(tmp, shaderPrefix);
//		strcat(tmp, fsPath);
//		s->Init(strcat(strcpy(prefix, shaderPrefix), vsPath),
//		        tmp);
//		int numStates;
//		fscanf(pfile, "STATES %d\n", &numStates);
//		for (int j = 0; j < numStates; j++)
//		{
//			char type[MAX_CHAR_LENGTH];
//			fscanf(pfile, "STATE %s\n", type);
//			if (strcmp(type, "CULLING") == 0)
//			{
//				s->states.push_back(ShaderState::CULLING);
//			}
//			if (strcmp(type, "DEPTH_TEST") == 0)
//			{
//				s->states.push_back(ShaderState::DEPTH_TEST);
//			}
//			if (strcmp(type, "ALPHA") == 0)
//			{
//				s->states.push_back(ShaderState::ALPHA);
//			}
//		}
//		m_mapShaders->insert(std::pair<int, Shaders*>(id, s));
//	}
//
//	fclose(pfile);
