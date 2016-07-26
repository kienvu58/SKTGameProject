#pragma once
#include "Texture.h"
class SpriteSheet :
	public Texture
{
public:
	SpriteSheet();
	SpriteSheet(int ID, int nRows, int nCols);
	~SpriteSheet();
	Vector2 GetDeltaByIndex(int index) const;
private:
	int m_iNRows;
	int m_iNColumns;
};

