#pragma once
#include "../Utilities/utilities.h"
#include "../Utilities/TGA.h"
#include <vector>
class CubeTexture
{
private:
	GLuint m_iTextureId;
	void SetTextureParameter();
public:
	CubeTexture();
	~CubeTexture();
	GLuint GetId() { return m_iTextureId; };
	void LoadTGAFiles(std::vector<char*> texturePaths);
};

