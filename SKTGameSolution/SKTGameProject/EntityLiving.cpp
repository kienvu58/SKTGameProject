#include "EntityLiving.h"
#include "../GraphicsEngine/ResourceManager.h"


EntityLiving::EntityLiving():currentFrame(0), delay(0)
{
}


EntityLiving::~EntityLiving()
{
}

void EntityLiving::Update()
{
}

void EntityLiving::InitSprite(int modelId, int spriteSheetId, int shadersId)
{
	m_Sprite.SetModel(ResourceMgr->GetModelById(modelId));
	m_Sprite.SetTexture(ResourceMgr->GetSpriteSheetById(spriteSheetId));
	m_Sprite.SetShaders(ResourceMgr->GetShadersById(shadersId));
}

void EntityLiving::InitAnimations(std::map<std::string, Animation*> mapAnimations)
{
	m_mapAnimations = mapAnimations;
}

void EntityLiving::SetFrameToSprite(Frame* frame)
{
	m_Sprite.SetTexture(ResourceMgr->GetSpriteSheetById(frame->GetSpriteSheetId()));
	m_Sprite.SetIndex(frame->GetIndex());
}

Animation* EntityLiving::GetAnimationByName(std::string name)
{
	auto it = m_mapAnimations.find(name);
	if (it == m_mapAnimations.end())
	{
		return nullptr;
	}
	return it->second;
}