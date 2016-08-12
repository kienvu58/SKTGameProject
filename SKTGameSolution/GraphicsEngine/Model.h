#pragma once
#include "../Utilities/utilities.h"

struct Vertex;

class Model
{
public:
	Model();
	Model(int ID);
	~Model();
	void LoadModel(Vertex* vertices, int nVertices);
	void Init(int modelW, int modelH, int spriteW, int spriteH, int textureW, int textureH);
	GLuint GetVboID() const;
	GLuint GetIboID() const;
	int GetModelWidth() const;
	int GetModelHeight() const;
private:
	int m_iModelWidth;
	int m_iModelHeight;
	GLuint m_ID;
	GLuint m_VboID;
	GLuint m_IboID;
};

