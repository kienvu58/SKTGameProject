#pragma once

#include <map>
#include "Animation.h"

class AnimationManager
{
public:
	static AnimationManager* GetInstance();
	static void DestroyInstance();
	Animation* GetAnimationById(int id) const;
	void Init(const char *path);
	~AnimationManager();
private:
	std::map<int, Animation*> m_mapAnimations; 
	static AnimationManager *s_Instance;
	AnimationManager();
};


#define AnimationMgr AnimationManager::GetInstance()

