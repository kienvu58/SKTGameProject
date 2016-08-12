#include "SpriteSheet.h"


SpriteSheet::SpriteSheet(): m_iNRows(0), m_iNColumns(0)
{
}

SpriteSheet::SpriteSheet(int ID, int nRows, int nCols) : Texture(ID), m_iNRows(nRows), m_iNColumns(nCols)
{
}

SpriteSheet::~SpriteSheet()
{
}

Vector2 SpriteSheet::GetDeltaByIndex(int index) const
{
	Vector2 delta;
	int indexRow, indexCol;
	indexRow = index / m_iNColumns;
	indexCol = index % m_iNColumns;

	delta.x = 1.0f / m_iNColumns * indexCol;
	delta.y = -1.0f / m_iNRows * indexRow;
	return delta;
}
