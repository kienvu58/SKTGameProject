#include "EntityLiving.h"
#include "../GraphicsEngine/ResourceManager.h"
#include "PhysicsManager.h"
#include <Box2D/Dynamics/b2Fixture.h>
#include <ostream>
#include <iostream>


EntityLiving::EntityLiving():currentFrame(0), delay(0)
{
}


EntityLiving::~EntityLiving()
{
}

void EntityLiving::Update()
{
	Vector2 position;
	position.x = PixelsFromMeters(m_pBody->GetPosition().x);
	position.y = PixelsFromMeters(m_pBody->GetPosition().y);
	
	b2Vec2 m = m_pBody->GetLinearVelocity();
	m_Sprite.SetPosition(position);
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

void EntityLiving::SetSpriteData(int index, Vector2 position)
{
	m_Sprite.SetIndex(index);
	m_Sprite.SetPosition(position);
}

void EntityLiving::InitBody(b2BodyDef &bodyDef, b2FixtureDef &fixtureDef)
{
	m_pBody = PhysicsMgr->GetWorld()->CreateBody(&bodyDef);
	m_pBody->CreateFixture(&fixtureDef);
	m_pBody->SetLinearVelocity(b2Vec2(-3, 0));
}

void EntityLiving::Reset()
{
}
