#pragma once
#include <vector>
#include "Frame.h"

class Animation
{
public:
	Animation();
	~Animation();

	void Reset();
	const Frame& GetNextFrame() const;
private:
	std::vector<Frame*> m_Frames;
	int m_iFrameCount;
	int m_iCurrentFrame;
	int m_iTotalFrames;
	bool m_bIsStopped;
};

