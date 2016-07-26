#pragma once
#include <vector>
#include "Frame.h"

class Animation
{
public:
	Animation(int id);
	~Animation();

	void Init(std::vector<int> frameIds);
	void Reset();
	Frame* GetNextFrame();
private:
	std::vector<Frame*> m_Frames;
	int m_iDelay;
	int m_iCurrentFrame;
	int m_iTotalFrames;
	int m_Id;
};

