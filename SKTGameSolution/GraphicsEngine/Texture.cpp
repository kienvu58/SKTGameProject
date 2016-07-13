#include "stdafx.h"
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

void Texture::LoadTGAFile(char* filePath) {
	glBindTexture(GL_TEXTURE_2D, m_iTextureId);
	int width, height, bpp;
	char *imageData = LoadTGA(filePath, &width, &height, &bpp);
	if (bpp == 24) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
	}
	else if (bpp == 32) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	}
	SetTextureParameter();
	glBindTexture(GL_TEXTURE_2D, 0);
	delete[] imageData;
}

void Texture::SetTextureParameter() {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}