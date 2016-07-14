#pragma once
#include "../Utilities/utilities.h"
#include <vector>

class CubeTexture
{
public:
	CubeTexture();
	~CubeTexture();
	GLuint GetId() const { return m_iTextureId;	};
	void LoadTGAFiles(std::vector<char*> texturePaths);
private:
	GLuint m_iTextureId;
	void SetTextureParameter();
};
