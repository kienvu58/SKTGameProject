#include "Sprite.h"
#include "ResourceManager.h"

Sprite::Sprite()
{
}


Sprite::~Sprite()
{
}

void Sprite::InitModel(float spriteX, float spriteY, float spriteW, float spriteH, float textureW, float textureH, Vector2 origin)
{
	Vertex* verticesData = new Vertex[4];
	verticesData[0].pos = Vector3(-(float)spriteW / 2, -(float)spriteH / 2, 0.0f);
	verticesData[1].pos = Vector3((float)spriteW / 2, -(float)spriteH / 2, 0.0f);
	verticesData[2].pos = Vector3(-(float)spriteW / 2, (float)spriteH / 2, 0.0f);
	verticesData[3].pos = Vector3((float)spriteW / 2, (float)spriteH / 2, 0.0f);
	
	verticesData[0].uv = Vector2((float)spriteX / textureW, (float)(textureH - spriteY - spriteH) / textureH);
	verticesData[1].uv = Vector2((float)(spriteX + spriteW) / textureW, (float)(textureH - spriteY - spriteH) / textureH);
	verticesData[2].uv = Vector2((float)spriteX / textureW, (float)(textureH - spriteY) / textureH);
	verticesData[3].uv = Vector2((float)(spriteX + spriteW) / textureW, (float)(textureH - spriteY) / textureH);

	m_pModel = new Model();
	m_pModel->Init(verticesData, 4);

	ResourceMgr->InsertModel(m_pModel);
}
