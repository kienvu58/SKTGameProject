#include "Texture.h"
#include "../Utilities/TGA.h"

Texture::Texture(): m_ID(0), m_TextureID(0)
{
}

Texture::~Texture()
{
}

GLuint Texture::GetTextureID() const
{
	return m_TextureID;
}

void Texture::LoadTGAFile(const char* filePath)
{
	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	int width, height, bpp;
	char* imageData = LoadTGA(filePath, &width, &height, &bpp);
	GLenum internalFormat = (bpp == 24) ? GL_RGB : GL_RGBA;
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, internalFormat, GL_UNSIGNED_BYTE, imageData);
	SetTextureParameter();
	glBindTexture(GL_TEXTURE_2D, 0);
	delete[] imageData;
}

void Texture::SetTextureParameter()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
