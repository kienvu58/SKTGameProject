#pragma once
#include "SpriteSheet.h"

class Frame
{
public:
	Frame(int id, int spriteSheetId, int index, int duration);
	~Frame();
	int GetSpriteSheetId() const;
	int GetIndex() const;
	int GetDuration() const;
private:
	int m_iDuration;
	int m_Index;
	int m_Id;
	int m_SpriteSheetId;
};

