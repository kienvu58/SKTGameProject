#include <json.hpp>
#include "ResourceManager.h"
#include <fstream>
#include "HelperFunctions.h"
#include "Shaders.h"
#include "../SKTGameProject/Definations.h"

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
		std::string spriteSheetPath(DATA_PATH);
		spriteSheetPath.append(path);
		spriteSheet->LoadTGAFile(spriteSheetPath.c_str());
		m_mapSpiteSheets.insert(std::pair<int, SpriteSheet*>(id, spriteSheet));
	}

	// init shaders
	for (auto it : data["shaders"])
	{
		int id;
		id = it["id"].get<int>();
		auto vs = it["vsPath"].get<std::string>();
		auto fs = it["fsPath"].get<std::string>();
		std::string vsPath(DATA_PATH);
		vsPath.append(vs);
		std::string fsPath(DATA_PATH);
		fsPath.append(fs);
		Shaders* shader = new Shaders();
		shader->Init(vsPath.c_str(), fsPath.c_str());
		m_mapShaders.insert(std::pair<int, Shaders*>(id, shader));
	}
}
