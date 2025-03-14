#include <json.hpp>
#include "AnimationManager.h"
#include <fstream>
#include "HelperFunctions.h"


AnimationManager::AnimationManager()
{
}

AnimationManager::~AnimationManager()
{
	ClearMap<Animation>(m_mapAnimations);
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
		int id, nStartFrames;
		id = it["id"].get<int>();
		nStartFrames = it["nStartFrames"].get<int>();
		Animation* animation = new Animation(id, nStartFrames);
		animation->Init(it["frameIDs"].get<std::vector<int>>());

		m_mapAnimations.insert(std::pair<int, Animation*>(id, animation));
	}
}

