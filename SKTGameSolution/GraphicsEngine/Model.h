#pragma once
#include "../Utilities/utilities.h"
#include "Vertex.h"

class Model
{
private:
	Vertex *m_pVertices;
	unsigned int *m_pIndices;
	int m_iNumVertices;
	int m_iNumIndices;
	GLuint m_iVboId;
	GLuint m_iIboId;
public:
	Model();
	~Model();
	void LoadModel(char *filePath);
	Vertex* GetVertices() const	{ return m_pVertices; };
	unsigned int* GetIndices() const { return m_pIndices; };
	int GetNumVertices() const { return m_iNumVertices; }
	int GetNumIndices() const { return m_iNumIndices; }
	int GetSizeVertices() const { return m_iNumVertices * sizeof(Vertex); }
	int GetSizeIndices() const { return m_iNumIndices * sizeof(unsigned int); }
	void Clear() const { if (m_pIndices)delete[] m_pIndices; delete[] m_pVertices; }
	GLuint GetVboId() const	{ return m_iVboId; }
	GLuint GetIboId() const	{ return m_iIboId; }
	void Init(char* filePath, char* heightMapPath);
	void SetHeightMap(char* filePath);
	void Init(Vertex* vertices, int numVertices);
};

