#include "TextManager.h"
#include "Globals.h"


int TextManager::Init(char * fileName)
{
	if (FT_Init_FreeType(&m_ft))
	{
		printf("Could not init freetype library\n");
		return 1;
	}
	if (FT_New_Face(m_ft, fileName, 0, &m_face)) {
		printf("Could not open font arial.ttf\n");
		return 1;
	}

	glGenTextures(1, &tex);
	glGenBuffers(1, &vbo);

	m_glyphSlot = m_face->glyph;
	//creation of shaders and program 
	return shaders->Init("../Resources/Shaders/TextVS.vs", "../Resources/Shaders/TextFS.fs");
}

void TextManager::RenderString(const char * text, Vector4 color, float size, float x, float y, float scaleX, float scaleY)
{
	//printf("render");
	//Set font size
	FT_Set_Pixel_Sizes(m_face, 0, size);

	glUseProgram(shaders->program);
	glUniform1i(shaders->locationUniformTexture, 0);

	//init. use single texture object render all the glyphs
	glActiveTexture(GL_TEXTURE0);
	
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	//set up a vertex buffer object
	
	glEnableVertexAttribArray(shaders->locationAttributePosition);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(shaders->locationAttributePosition, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Set coordinate y to bottomleft from topleft.
	y = -y;
	y += (Globals::screenHeight) - size / 2;

	//Text color
	glUniform4fv(shaders->locationUniformColor, 1, &color.x);

	float sx = 1.0f / Globals::screenWidth * scaleX;
	float sy = 1.0f / Globals::screenHeight * scaleY;
	x = -1.0f + 2.0f * x / Globals::screenWidth;
	y = (-1.0f + 2.0f * y / Globals::screenHeight);
	for (const char *p = text; *p; p++)
	{
		if (FT_Load_Char(m_face, *p, FT_LOAD_RENDER))
		{
			continue;
		}
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_ALPHA,
			m_glyphSlot->bitmap.width,
			m_glyphSlot->bitmap.rows,
			0,
			GL_ALPHA,
			GL_UNSIGNED_BYTE,
			m_glyphSlot->bitmap.buffer
		);
		float x2 = x + m_glyphSlot->bitmap_left * sx;
		float y2 = -y - m_glyphSlot->bitmap_top * sy;
		float w = m_glyphSlot->bitmap.width * sx;
		float h = m_glyphSlot->bitmap.rows * sy;


		GLfloat box[4][4] = {
			{ x2, -y2 , 0, 0 },
			{ x2 + w, -y2 , 1, 0 },
			{ x2, -y2 - h, 0, 1 },
			{ x2 + w, -y2 - h, 1, 1 },
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_DYNAMIC_DRAW);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		x += (m_glyphSlot->advance.x >> 6) * sx;
		y += (m_glyphSlot->advance.y >> 6) * sy;
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}


TextManager::TextManager()
{
}

TextManager::~TextManager()
{
	delete shaders;
}
