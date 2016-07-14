#include "CubeTexture.h"
#include <iostream>

CubeTexture::CubeTexture()
{
	glGenTextures(1, &m_iTextureId);
}

CubeTexture::~CubeTexture()
{
}

void CubeTexture::LoadTGAFiles(std::vector<char*> texturePaths) {
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_iTextureId);

	for (int i = 0; i < texturePaths.size(); i++) {
		int width, height, bpp;
		char *imageData = LoadTGA(texturePaths[i], &width, &height, &bpp);
		GLenum internalFormat = (bpp == 24) ? GL_RGB : GL_RGBA;
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internalFormat, width, height, 0, internalFormat, GL_UNSIGNED_BYTE, imageData);
		delete[] imageData;
	}

	SetTextureParameter();

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
void CubeTexture::SetTextureParameter() {
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}