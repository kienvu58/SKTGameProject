#include <json.hpp>
#include "FrameManager.h"
#include <fstream>
#include "Camera.h"
#include "HelperFunctions.h"


FrameManager* FrameManager::s_Instance = nullptr;

FrameManager::FrameManager()
{
};

FrameManager::~FrameManager()
{
	ClearMap<Frame>(m_mapFrames);
}

FrameManager* FrameManager::GetInstance()
{
	if (s_Instance == nullptr)
	{
		s_Instance = new FrameManager();
	}
	return s_Instance;
}

void FrameManager::DestroyInstance()
{
	if (s_Instance)
	{
		delete s_Instance;
		s_Instance = nullptr;
	}
}

void FrameManager::Init(const char* path)
{
	std::ifstream fin(path);
	nlohmann::json data(fin);
	fin.close();

	// Init frames
	for (auto it : data["frames"])
	{
		int id, spriteSheetId, index, duration;
		id = it["id"].get<int>();
		spriteSheetId = it["spriteSheetID"].get<int>();
		index = it["index"].get<int>();
		duration = it["duration"].get<int>();

		Frame* frame = new Frame(id, spriteSheetId, index, duration);
		m_mapFrames.insert(std::pair<int, Frame*>(id, frame));
	}
}

Frame* FrameManager::GetFrameById(int id) const
{
	return GetResourceById<Frame>(id, m_mapFrames);
}
