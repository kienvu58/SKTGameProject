#include "Model.h"
#include "Vertex.h"

//#include <iostream>
//#include <fstream>
//
//Model::Model(): m_pVertices(nullptr),
//                m_pIndices(nullptr),
//                m_iNumVertices(0),
//                m_iNumIndices(0),
//                m_iVboId(0),
//                m_iIboId(0)
//{
//}
//
//Model::~Model()
//{
//}
//
//void Model::LoadModel(char* filePath)
//{
//	FILE* pFile;
//	pFile = fopen(filePath, "r");
//	if (!pFile)
//	{
//		std::cout << "Could not open file " << filePath << std::endl;
//	}
//
//	fscanf(pFile, "NrVertices: %d\n", &m_iNumVertices);
//	m_pVertices = new Vertex[m_iNumVertices];
//
//	int i;
//	for (i = 0; i < m_iNumVertices; i++)
//	{
//		fscanf(pFile, "%*d. pos:[%f, %f, %f]; norm:[%*f, %*f, %*f]; binorm:[%*f, %*f, %*f]; tgt:[%*f, %*f, %*f]; uv:[%f, %f];\n",
//		       &(m_pVertices[i].pos.x),
//		       &(m_pVertices[i].pos.y),
//		       &(m_pVertices[i].pos.z),
//		       &(m_pVertices[i].uv.x),
//		       &(m_pVertices[i].uv.y)
//		);
//	}
//
//	fscanf(pFile, "NrIndices: %d\n", &m_iNumIndices);
//	m_pIndices = new unsigned int[m_iNumIndices];
//
//	for (i = 0; i < m_iNumIndices; i++)
//	{
//		fscanf(pFile, "%*d.    %d,    %d,    %d",
//		       &(m_pIndices[i * 3]), &(m_pIndices[i * 3 + 1]), &(m_pIndices[i * 3 + 2])
//		);
//	}
//	fclose(pFile);
//}
//
//void Model::Init(char* filePath, char* heightMapPath)
//{
//	LoadModel(filePath);
//	//triangle data (heap)
//	Vertex* verticesData = GetVertices();
//
//	//read height map
//	if (heightMapPath != nullptr)
//	{
//		SetHeightMap(heightMapPath);
//	}
//
//	//buffer object
//	glGenBuffers(1, &m_iVboId);
//	glBindBuffer(GL_ARRAY_BUFFER, m_iVboId);
//	glBufferData(GL_ARRAY_BUFFER, GetSizeVertices(), verticesData, GL_STATIC_DRAW);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//	//buffer object
//	unsigned int* indices = GetIndices();
//
//	glGenBuffers(1, &m_iIboId);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iIboId);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, GetSizeIndices(), indices, GL_STATIC_DRAW);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//
//	this->Clear();
//}
//
//void Model::SetHeightMap(char* filePath)
//{
//	std::ifstream inFile(filePath,
//	                     std::ifstream::in | std::ifstream::binary | std::ifstream::ate);
//
//	char* data;
//	int size = inFile.tellg();
//	inFile.seekg(0, std::ifstream::beg);
//	data = new char[size];
//
//	if (inFile.is_open())
//		inFile.read(data, size);
//
//	for (int i = 0; i < size; i++)
//	{
//		m_pVertices[i].pos.y = static_cast<unsigned char>(data[i]);
//	}
//	delete []data;
//}
//
///*This init function for sprite*/
//void Model::Init(Vertex* vertices, int numVertices)
//{
//	m_pVertices = vertices;
//	m_iNumVertices = numVertices;
//	//buffer object
//	glGenBuffers(1, &m_iVboId);
//	glBindBuffer(GL_ARRAY_BUFFER, m_iVboId);
//	glBufferData(GL_ARRAY_BUFFER, GetSizeVertices(), m_pVertices, GL_STATIC_DRAW);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//	this->Clear();
//};

Model::Model(): m_ID(0), m_VboID(0), m_IboID(0)
{
}

Model::Model(int ID): m_ID(ID), m_VboID(0), m_IboID(0)
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

void Model::Init(int spriteX, int spriteY, int spriteW, int spriteH, int textureW, int textureH)
{
	Vertex verticesData[4];
	verticesData[0].pos = Vector3(-(float)spriteW / 2, -(float)spriteH / 2, 0.0f);
	verticesData[1].pos = Vector3((float)spriteW / 2, -(float)spriteH / 2, 0.0f);
	verticesData[2].pos = Vector3(-(float)spriteW / 2, (float)spriteH / 2, 0.0f);
	verticesData[3].pos = Vector3((float)spriteW / 2, (float)spriteH / 2, 0.0f);

	verticesData[0].uv = Vector2((float)spriteX / textureW, (float)(textureH - spriteY - spriteH) / textureH);
	verticesData[1].uv = Vector2((float)(spriteX + spriteW) / textureW, (float)(textureH - spriteY - spriteH) / textureH);
	verticesData[2].uv = Vector2((float)spriteX / textureW, (float)(textureH - spriteY) / textureH);
	verticesData[3].uv = Vector2((float)(spriteX + spriteW) / textureW, (float)(textureH - spriteY) / textureH);
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
