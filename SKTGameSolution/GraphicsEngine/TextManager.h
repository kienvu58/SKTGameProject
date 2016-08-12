#pragma once
#include "../Utilities/utilities.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include "Shaders.h"
class TextManager
{
public:
	TextManager();
	~TextManager();

	Shaders *shaders = new Shaders();
	FT_Library m_ft;
	FT_Face m_face;
	FT_GlyphSlot m_glyphSlot;
	GLuint vbo;
	unsigned int tex;

	int Init(const char *fileName);
	void RenderString(const char *text, Vector4 color, float size, float x, float y, float scaleX, float scaleY) const;
};
