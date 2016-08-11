#pragma once

class Frame
{
public:
	Frame(int id, int spriteSheetId, int index, float duration);
	~Frame();
	int GetSpriteSheetId() const;
	int GetIndex() const;
	int GetDuration() const;
private:
	float m_fDuration;
	int m_Index;
	int m_Id;
	int m_SpriteSheetId;
};

