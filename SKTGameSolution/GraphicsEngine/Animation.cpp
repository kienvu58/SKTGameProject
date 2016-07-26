#include "Animation.h"
#include <iostream>
#include "FrameManager.h"


Animation::Animation(int id): m_iDelay(0), m_iCurrentFrame(0), m_iTotalFrames(0), m_Id(id) {
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

void Animation::Reset()
{
	m_iCurrentFrame = 0;
	m_iDelay = 0;
}

Frame* Animation::GetNextFrame()
{
	m_iDelay++;
	if (m_iDelay > m_Frames.at(m_iCurrentFrame)->GetDuration())
	{
		m_iCurrentFrame++;
		m_iCurrentFrame %= m_iTotalFrames;
	}
	return m_Frames.at(m_iCurrentFrame);
}
