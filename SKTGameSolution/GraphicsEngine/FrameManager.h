#pragma once

#include <map>
#include "Animation.h"

class FrameManager
{
public:
	FrameManager();
	~FrameManager();

	void Init(const char *path);
	Frame* GetFrameById(int id) const;
private:
	std::map<int, Frame*> m_mapFrames;
};


