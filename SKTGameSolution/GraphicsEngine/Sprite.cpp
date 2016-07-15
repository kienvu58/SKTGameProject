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
	Vector3 delta = Vector3(origin.x - (float)spriteW /2, origin.y - (float)spriteH/2, 0.0f);
	Vertex *verticesData = new Vertex[4];
	verticesData[0].pos = Vector3(-(float)spriteW / 2, -(float)spriteH / 2, 0.0f) - delta;
	verticesData[1].pos = Vector3((float)spriteW / 2, -(float)spriteH / 2, 0.0f) - delta;
	verticesData[2].pos = Vector3(-(float)spriteW / 2, (float)spriteH / 2, 0.0f) - delta;
	verticesData[3].pos = Vector3((float)spriteW / 2, (float)spriteH / 2, 0.0f) - delta;
	verticesData[0].uv = Vector2((float)spriteX / textureW, (float)(spriteY + spriteH) / textureH);
	verticesData[1].uv = Vector2((float)(spriteX + spriteW) / textureW, (float)(spriteY + spriteH) / textureH);
	verticesData[2].uv = Vector2((float)spriteX / textureW, (float)spriteY / textureH);
	verticesData[3].uv = Vector2((float)(spriteX + spriteW) / textureW, (float)spriteY / textureH);
	
	m_pModel = new Model();
	m_pModel->Init(verticesData, 4);
	
	ResourceMgr->InsertModel(m_pModel);
}
