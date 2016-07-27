#include <json.hpp>
#include "AnimationManager.h"
#include <fstream>
#include "Camera.h"
#include "HelperFunctions.h"


AnimationManager* AnimationManager::s_Instance = nullptr;

AnimationManager::AnimationManager()
{
}

AnimationManager::~AnimationManager()
{
	ClearMap<Animation>(m_mapAnimations);
}

AnimationManager* AnimationManager::GetInstance()
{
	if (s_Instance == nullptr)
	{
		s_Instance = new AnimationManager();
	}
	return s_Instance;
}

void AnimationManager::DestroyInstance()
{
	if (s_Instance)
	{
		delete s_Instance;
		s_Instance = nullptr;
	}
}

Animation* AnimationManager::GetAnimationById(int id) const
{
	return GetResourceById<Animation>(id, m_mapAnimations);
}

void AnimationManager::Init(const char* path)
{
	std::ifstream fin(path);
	nlohmann::json data(fin);
	fin.close();

	// Init animations
	for (auto it : data["animations"])
	{
		int id;
		id = it["id"].get<int>();
		Animation* animation = new Animation(id);
		animation->Init(it["frameIDs"].get<std::vector<int>>());

		m_mapAnimations.insert(std::pair<int, Animation*>(id, animation));
	}
}

