#include "EntityStatic.h"
#include "../GraphicsEngine/ResourceManager.h"


EntityStatic::EntityStatic()
{
}

void EntityStatic::Render()
{
}

void EntityStatic::Update()
{
}

void EntityStatic::InitSprite(int modelId, int frameId, int shaderId)
{
	m_Sprite.SetModel(ResourceMgr->GetModelById(modelId));
	m_Sprite.SetShaders(ResourceMgr->GetShadersById(shaderId));
}

EntityStatic::~EntityStatic()
{
}
