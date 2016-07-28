#include "Animation.h"
#include <iostream>
#include "FrameManager.h"


Animation::Animation(int id): m_iTotalFrames(0), m_Id(id) {
}


Animation::~Animation()
{
}

void Animation::Init(std::vector<int> frameIds)
{
	m_iTotalFrames = frameIds.size();
	for(auto it : frameIds)
	{
		m_Frames.push_back(FrameMgr->GetFrameById(it));
	}
}

Frame* Animation::GetNextFrame(int currentFrame, float delay)
{
	if (currentFrame > m_iTotalFrames)
	{
		return nullptr;
	}

	if (int(++delay) > m_Frames.at(currentFrame)->GetDuration())
	{
		currentFrame++;
		currentFrame %= m_iTotalFrames;
	}
	return m_Frames.at(currentFrame);
}
