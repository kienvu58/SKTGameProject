#pragma once

#include <map>
#include "Animation.h"

class FrameManager
{
public:
	static FrameManager* GetInstance();
	static void DestroyInstance();
	void Init(const char *path);
	Frame* GetFrameById(int id) const;
	~FrameManager();
private:
	std::map<int, Frame*> m_mapFrames;
	static FrameManager *s_Instance;
	FrameManager();
};


#define FrameMgr FrameManager::GetInstance()

