#pragma once

#include <map>
#include "Animation.h"

class AnimationManager
{
public:
	AnimationManager();
	~AnimationManager();

	Animation* GetAnimationById(int id) const;
	void Init(const char *path);
private:
	std::map<int, Animation*> m_mapAnimations; 
};


