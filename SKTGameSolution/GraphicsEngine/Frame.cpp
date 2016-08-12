#include "Frame.h"


Frame::Frame(int ID, int spriteSheetID, int index, float duration): m_fDuration(duration), m_Index(index), m_Id(ID), m_SpriteSheetId(spriteSheetID)
{
}

Frame::~Frame()
{
}

int Frame::GetSpriteSheetId() const
{
	return m_SpriteSheetId;
}

int Frame::GetIndex() const
{
	return m_Index;
}

int Frame::GetDuration() const
{
	return m_fDuration;
}
