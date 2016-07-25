#pragma once
#include "Texture.h"

class Frame
{
public:
	Frame();
	~Frame();
private:
	Texture* m_pSpriteSheet;
	int m_iIndex;
	int m_iDuration;
};

