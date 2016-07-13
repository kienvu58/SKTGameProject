#include "Model.h"
#include <iostream>
#include <fstream>

Model::~Model()
{

}

void Model::LoadModel(char *filePath) {
	FILE *pFile;
	pFile = fopen(filePath, "r");
	if (!pFile) {
		std::cout << "Could not open file " << filePath << std::endl;
	}

	fscanf(pFile, "NrVertices: %d\n", &m_iNumVertices);
	m_pVertices = new Vertex[m_iNumVertices];
	
	int i;
	for (i = 0; i < m_iNumVertices; i++) {
		fscanf(pFile, "%*d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];\n", 
			&(m_pVertices[i].pos.x),
			&(m_pVertices[i].pos.y),
			&(m_pVertices[i].pos.z),
			&(m_pVertices[i].norm.x),
			&(m_pVertices[i].norm.y),
			&(m_pVertices[i].norm.z),
			&(m_pVertices[i].binorm.x),
			&(m_pVertices[i].binorm.y),
			&(m_pVertices[i].binorm.z),
			&(m_pVertices[i].tgt.x),
			&(m_pVertices[i].tgt.y),
			&(m_pVertices[i].tgt.z),
			&(m_pVertices[i].uv.x),
			&(m_pVertices[i].uv.y)
			);
	}

	fscanf(pFile, "NrIndices: %d\n", &m_iNumIndices);
	m_pIndices = new unsigned int[m_iNumIndices];

	for (i = 0; i < m_iNumIndices; i++) {
		fscanf(pFile, "%*d.    %d,    %d,    %d", 
			&(m_pIndices[i*3]), &(m_pIndices[i * 3 + 1]), &(m_pIndices[i * 3 + 2])
			);
	}
}

void Model::Init(char* filePath, char* heightMapPath){
	LoadModel(filePath);
	//triangle data (heap)
	Vertex *verticesData = GetVertices();

	//read height map
	if (heightMapPath != 0) {
		SetHeightMap(heightMapPath);
	}

	//buffer object
	glGenBuffers(1, &m_iVboId);
	glBindBuffer(GL_ARRAY_BUFFER, m_iVboId);
	glBufferData(GL_ARRAY_BUFFER, GetSizeVertices(), verticesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//buffer object
	unsigned int *indices = GetIndices();
	
	glGenBuffers(1, &m_iIboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iIboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, GetSizeIndices(), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	this->Clear();
}

void Model::SetHeightMap(char* filePath) {
	std::ifstream inFile(filePath,
	std::ifstream::in | std::ifstream::binary | std::ifstream::ate);
	
	char* data;
	int size = inFile.tellg();
	inFile.seekg(0, std::ifstream::beg);
	data = new char[size];

	if (inFile.is_open())
		inFile.read(data, size);

	for (int i = 0; i < size; i++) {
		m_pVertices[i].pos.y = float((unsigned char)data[i]);
	}
	delete []data;
}