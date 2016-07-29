#include "EntityStatic.h"
#include "../GraphicsEngine/ResourceManager.h"
#include "../GraphicsEngine/FrameManager.h"
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
	m_Sprite.SetPosition(Vector2(x, y));
}

EntityStatic::~EntityStatic()
{
}
