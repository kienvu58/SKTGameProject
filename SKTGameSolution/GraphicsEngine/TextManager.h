#pragma once
#include <vector>
#include "../Utilities/utilities.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include "Globals.h"
#include "Shaders.h"
class TextManager
{
private:
	static TextManager* s_Instance;
public:
	static TextManager* GetInstance();
	Shaders *shaders = new Shaders();
	FT_Library m_ft;
	FT_Face m_face;
	FT_GlyphSlot m_glyphSlot;
	GLuint vbo;
	unsigned int tex;

	TextManager();
	int Init(char *fileName);
	void RenderString(const char *text, Vector4 color, float size, float x, float y, float scaleX, float scaleY);
	void DestroyInstance();
	void DestroyShaders();
	~TextManager();
};

#define TextMgr TextManager::GetInstance()