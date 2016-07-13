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
	Model() :m_pVertices(0),
		     m_pIndices(0),
			 m_iNumVertices(0),
			 m_iNumIndices(0)
			 {};
	~Model();
	void LoadModel(char *filePath);
	Vertex* GetVertices() { return m_pVertices; };
	unsigned int* GetIndices() { return m_pIndices; };
	int GetNumVertices() { return m_iNumVertices; }
	int GetNumIndices() { return m_iNumIndices; }
	int GetSizeVertices() { return m_iNumVertices * sizeof(Vertex); }
	int GetSizeIndices() { return m_iNumIndices * sizeof(unsigned int); }
	void Clear() { delete[] m_pIndices; delete[] m_pVertices; }
	GLuint GetVboId() { return m_iVboId; }
	GLuint GetIboId() { return m_iIboId; }
	void Init(char* filePath, char* heightMapPath);
	void SetHeightMap(char* filePath);
};

