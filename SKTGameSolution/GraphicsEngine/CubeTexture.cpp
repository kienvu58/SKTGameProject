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
		char *image = LoadTGA(texturePaths[i], &width, &height, &bpp);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		delete[] image;
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