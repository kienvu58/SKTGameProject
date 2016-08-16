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

void EntityStatic::SetScreenPosition(int x, int y)
{
	m_ScreenPosition.x = x;
	m_ScreenPosition.y = y;
	m_WorldPosition.x = x - Globals::screenWidth / 2;
	m_WorldPosition.y = -y + Globals::screenHeight / 2;
	m_Sprite.SetRenderInfo(m_WorldPosition);
}

Sprite& EntityStatic::GetSprite()
{
	return m_Sprite;
}

bool EntityStatic::IsClicked(Vector2 mousePosition) const
{
	auto halfWidth = float(m_Sprite.GetModel()->GetModelWidth()) / 2;
	auto halfHeight = float(m_Sprite.GetModel()->GetModelHeight()) / 2;

	auto left = m_ScreenPosition.x - halfWidth;
	auto right = m_ScreenPosition.x + halfWidth;
	auto top = m_ScreenPosition.y - halfHeight;
	auto bottom = m_ScreenPosition.y + halfHeight;



	auto insideBoundaryX = left <= mousePosition.x && mousePosition.x <= right;
	auto insideBoundaryY = top <= mousePosition.y && mousePosition.y <= bottom;
	
	auto isClicked = insideBoundaryX && insideBoundaryY;

	return isClicked;
}

Vector2 EntityStatic::GetWorldPosition() const
{
	return m_WorldPosition;
}

Vector2 EntityStatic::GetScreenPosition() const
{
	return m_ScreenPosition;
}

EntityStatic::~EntityStatic()
{
}
