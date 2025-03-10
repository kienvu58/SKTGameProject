#pragma once
#include <vector>
#include "Frame.h"

class Animation
{
public:
	explicit Animation(int id, int nStartFrames);
	~Animation();

	void Init(std::vector<int> frameIds);
	Frame* GetFrameByIndex(int index) const;
	int GetNextFrameIndex(int currentFrame, float delay);
	int GetTotalFrames() const;
	int GetNStartFrame() const;
private:
	std::vector<Frame*> m_Frames;
	int m_iTotalFrames;
	int m_iNStartFrames;
	int m_Id;
};

