#pragma once
#include "../Utilities/utilities.h"

class Texture
{
public:
	Texture();
	~Texture();
	GLuint GetId() const { return m_iTextureId;	};
	void LoadTGAFile(char* filePath);
private:
	GLuint m_iTextureId;
	void SetTextureParameter();
};
