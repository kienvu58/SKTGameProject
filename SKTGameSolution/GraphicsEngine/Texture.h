#pragma once
#include "../Utilities/utilities.h"
class Texture
{
private:
	GLuint m_iTextureId;
	void SetTextureParameter();
public:
	Texture();
	~Texture();
	GLuint GetId() { return m_iTextureId; };
	void LoadTGAFile(char* filePath);
};

