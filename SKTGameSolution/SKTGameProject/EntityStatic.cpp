#include "EntityStatic.h"
#include "SingletonClasses.h"
#include "../GraphicsEngine/Globals.h"


EntityStatic::EntityStatic()
{
}

void EntityStatic::Render()
{
	m_Sprite.Render();
}

void EntityStatic::Update()
{
}

bool EntityStatic::HandleMessage(const Telegram& telegram)
{
	return false;
}

EntityType EntityStatic::GetType()
{
	return ENTITY_STATIC;
}

Entity* EntityStatic::Clone()
{
	return nullptr;
}

void EntityStatic::InitSprite(int modelId, int frameId, int shaderId)
{
	m_Sprite.SetModel(ResourceMgr->GetModelById(modelId));
	m_Sprite.SetShaders(ResourceMgr->GetShadersById(shaderId));
	m_Sprite.SetFrame(FrameMgr->GetFrameById(frameId));
}

void EntityStatic::InitPosition(int x, int y)
{
	x = x - Globals::screenWidth / 2;
	y = -y + Globals::screenHeight / 2;
	m_Sprite.SetRenderInfo(Vector2(x, y));
}

Sprite& EntityStatic::GetSprite()
{
	return m_Sprite;
}

EntityStatic::~EntityStatic()
{
}
