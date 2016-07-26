#pragma once
#include "../Utilities/utilities.h"

class Texture
{
public:
	Texture();
	explicit Texture(int ID);
	~Texture();
	GLuint GetTextureID() const;
	void LoadTGAFile(const char* filePath);
private:
	GLuint m_ID;
	GLuint m_TextureID;
	static void SetTextureParameter();
};
