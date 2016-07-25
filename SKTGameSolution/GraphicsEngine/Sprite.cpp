#include "Sprite.h"
#include "../Utilities/utilities.h"
#include <GLES2/gl2.h>
#include "Vertex.h"

Sprite::Sprite(): m_iIndex(0)
{
}


Sprite::~Sprite()
{
}

void Sprite::Render()
{
	glUseProgram(m_pShaders->program);
	glBindBuffer(GL_ARRAY_BUFFER, m_pModel->GetVboID());
	glBindTexture(GL_TEXTURE_2D, m_pTexture->GetTextureID());
	GLuint posLocation = m_pShaders->locationAttributePos;
	if (posLocation != -1)
	{
		glEnableVertexAttribArray(posLocation);
		glVertexAttribPointer(m_pShaders->locationAttributePos, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, pos)));
	}
	GLuint uvLocation = m_pShaders->locationAttributeUV;
	if (uvLocation != -1)
	{
		glEnableVertexAttribArray(uvLocation);
		glVertexAttribPointer(uvLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, uv)));
	}
	GLuint iTexLocation = m_pShaders->locationUniformTex;
	if (iTexLocation != -1)
	{
		glUniform1i(iTexLocation, 0);
	}
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Sprite::Update(void* data)
{
}

//void Sprite::InitModel(float spriteX, float spriteY, float spriteW, float spriteH, float textureW, float textureH, Vector2 origin)
//{
//	Vertex* verticesData = new Vertex[4];
//	verticesData[0].pos = Vector3(-(float)spriteW / 2, -(float)spriteH / 2, 0.0f);
//	verticesData[1].pos = Vector3((float)spriteW / 2, -(float)spriteH / 2, 0.0f);
//	verticesData[2].pos = Vector3(-(float)spriteW / 2, (float)spriteH / 2, 0.0f);
//	verticesData[3].pos = Vector3((float)spriteW / 2, (float)spriteH / 2, 0.0f);
//	
//	verticesData[0].uv = Vector2((float)spriteX / textureW, (float)(textureH - spriteY - spriteH) / textureH);
//	verticesData[1].uv = Vector2((float)(spriteX + spriteW) / textureW, (float)(textureH - spriteY - spriteH) / textureH);
//	verticesData[2].uv = Vector2((float)spriteX / textureW, (float)(textureH - spriteY) / textureH);
//	verticesData[3].uv = Vector2((float)(spriteX + spriteW) / textureW, (float)(textureH - spriteY) / textureH);
//
//	m_pModel = new Model();
//	m_pModel->Init(verticesData, 4);
//
//	ResourceMgr->InsertModel(m_pModel);
//}
