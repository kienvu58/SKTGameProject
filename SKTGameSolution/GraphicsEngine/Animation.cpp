#include "Animation.h"
#include "../SKTGameProject/SingletonClasses.h"


Animation::Animation(int id, int nStartFrames): m_iTotalFrames(0), m_iNStartFrames(nStartFrames), m_Id(id)
{
}


Animation::~Animation()
{
}

void Animation::Init(std::vector<int> frameIds)
{
	m_iTotalFrames = frameIds.size();
	for (auto it : frameIds)
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
		auto totalFrames = m_iTotalFrames;
		if (currentFrame >= m_iNStartFrames)
		{
			currentFrame -= m_iNStartFrames;
			totalFrames -= m_iNStartFrames;
			currentFrame %= totalFrames;
			currentFrame += m_iNStartFrames;
		}
		else
		{
			currentFrame %= totalFrames;
		}
	}
	return currentFrame;
}

int Animation::GetTotalFrames() const
{
	return m_iTotalFrames;
}

int Animation::GetNStartFrame() const
{
	return m_iNStartFrames;
}
