#include "Animation.h"
#include "../SKTGameProject/SingletonClasses.h"


Animation::Animation(int id, int nStartFrames): m_iTotalFrames(0), m_iNStartFrames(nStartFrames), m_Id(id) {
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

Frame* Animation::GetFrameByIndex(int index) const
{
	if (index > m_Frames.size())
	{
		return nullptr;
	}
	return m_Frames.at(index);
}

int Animation::GetNextFrameIndex(int currentFrame, float delay)
{

	if (delay >= m_Frames.at(currentFrame)->GetDuration())
	{
		currentFrame++;
		currentFrame %= m_iTotalFrames;
	}
	return currentFrame;
}

int Animation::GetTotalFrames() const
{
	return m_iTotalFrames;
}
