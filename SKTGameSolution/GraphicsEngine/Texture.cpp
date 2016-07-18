#include "Texture.h"
#include "../Utilities/TGA.h"
#include <iostream>

Texture::Texture()
{
	glGenTextures(1, &m_iTextureId);
}

Texture::~Texture()
{
}

void Texture::LoadTGAFile(char* filePath)
{
	glBindTexture(GL_TEXTURE_2D, m_iTextureId);
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
