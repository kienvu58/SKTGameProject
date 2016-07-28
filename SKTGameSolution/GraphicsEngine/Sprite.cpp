#include "Sprite.h"
#include "../Utilities/utilities.h"
#include <GLES2/gl2.h>
#include "Vertex.h"
#include "Globals.h"
#include "SpriteSheet.h"
#include "Frame.h"
#include "ResourceManager.h"

Sprite::Sprite(): m_Index(0) {
	m_matMVP.SetOrthographic(-static_cast<float>(Globals::screenWidth) / 2, static_cast<float>(Globals::screenWidth / 2),
	                         static_cast<float>(Globals::screenHeight / 2), -static_cast<float>(Globals::screenHeight / 2), 0.1, 40); 
}

Sprite::~Sprite()
{
}

void Sprite::SetFrame(Frame* frame)
{
	m_pTexture = ResourceMgr->GetSpriteSheetById(frame->GetSpriteSheetId());
	m_Index = frame->GetIndex();
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
		glVertexAttribPointer(posLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, pos)));
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
	GLuint mvpLocation = m_pShaders->locationUniformMVP;
	if (mvpLocation != -1)
	{
		glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &(m_matMVP.m[0][0]));
	}
	GLuint deltaLocation = m_pShaders->locationUniformDelta;
	if (deltaLocation != -1)
	{
		Vector2 vec2Delta;
		vec2Delta = static_cast<SpriteSheet*>(m_pTexture)->GetDeltaByIndex(m_Index);
		float delta[2];
		delta[0] = vec2Delta.x;
		delta[1] = vec2Delta.y;
		glUniform2fv(deltaLocation, 1, delta);
	}
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Sprite::SetPosition(Vector2 position)
{
	Matrix model, projection;
	model.SetTranslation(position.x, position.y, 0);
	projection.SetOrthographic(-static_cast<float>(Globals::screenWidth) / 2, static_cast<float>(Globals::screenWidth / 2),
		static_cast<float>(Globals::screenHeight / 2), -static_cast<float>(Globals::screenHeight / 2), 0.1, 40);
	m_matMVP = model * projection;
}

void Sprite::SetIndex(int index)
{
	m_Index = index;
}


//void Sprite::InitSprite(float spriteX, float spriteY, float spriteW, float spriteH, float textureW, float textureH, Vector2 origin)
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
