#pragma once
#include <vector>
#include "Frame.h"

class Animation
{
public:
	Animation(int id);
	~Animation();

	void Init(std::vector<int> frameIds);
	Frame* GetNextFrame(int& currentFrame, int& delay);
private:
	std::vector<Frame*> m_Frames;
	int m_iTotalFrames;
	int m_Id;
};

