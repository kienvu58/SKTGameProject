#include "Model.h"
#include "Vertex.h"


Model::Model(): m_iModelWidth(0), m_iModelHeight(0), m_ID(0), m_VboID(0), m_IboID(0)
{
}

Model::Model(int ID): m_iModelWidth(0), m_iModelHeight(0), m_ID(ID), m_VboID(0), m_IboID(0)
{
}

Model::~Model()
{
}

void Model::LoadModel(Vertex* vertices, int nVertices)
{
	glGenBuffers(1, &m_VboID);
	glBindBuffer(GL_ARRAY_BUFFER, m_VboID);
	glBufferData(GL_ARRAY_BUFFER, nVertices * sizeof(Vertex), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Model::Init(int modelW, int modelH, int spriteW, int spriteH, int textureW, int textureH)
{
	m_iModelWidth = modelW;
	m_iModelHeight = modelH;

	Vertex verticesData[4];
	verticesData[0].pos = Vector3(-float(modelW) / 2, -float(modelH) / 2, 0.0f);
	verticesData[1].pos = Vector3(float(modelW) / 2, -float(modelH) / 2, 0.0f);
	verticesData[2].pos = Vector3(-float(modelW) / 2, float(modelH) / 2, 0.0f);
	verticesData[3].pos = Vector3(float(modelW) / 2, float(modelH) / 2, 0.0f);

	verticesData[0].uv = Vector2(0, float(textureH - spriteH) / textureH);
	verticesData[1].uv = Vector2(float(spriteW) / textureW, float(textureH - spriteH) / textureH);
	verticesData[2].uv = Vector2(0, float(textureH) / textureH);
	verticesData[3].uv = Vector2(float(spriteW) / textureW, float(textureH) / textureH);
	LoadModel(verticesData, 4);
}

GLuint Model::GetVboID() const
{
	return m_VboID;
}

GLuint Model::GetIboID() const
{
	return m_IboID;
}

int Model::GetModelWidth() const
{
	return m_iModelWidth;
}

int Model::GetModelHeight() const
{
	return m_iModelHeight;
}
