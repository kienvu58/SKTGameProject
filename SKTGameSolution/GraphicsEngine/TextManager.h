#pragma once
#include <ft2build.h>"
#include FT_FREETYPE_H
#include "Shaders.h"
#include "../Utilities/utilities.h"

class TextManager
{
public:
	TextManager();
	~TextManager();

	Shaders* m_pShaders;
	FT_Library m_ftLibrary;
	FT_Face m_ftFace;
	FT_GlyphSlot m_ftGlyphSlot;
	GLuint m_VboId;
	GLuint m_TextureId;

	int Init(const char* fileName);
	void RenderString(const char* text, Vector4 color, float size, float x, float y, float scaleX, float scaleY) const;
};
