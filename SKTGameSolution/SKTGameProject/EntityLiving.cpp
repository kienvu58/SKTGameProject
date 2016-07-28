#include "EntityLiving.h"
#include "../GraphicsEngine/ResourceManager.h"
#include "PhysicsManager.h"
#include <Box2D/Dynamics/b2Fixture.h>
#include <ostream>
#include <iostream>
#include "../GraphicsEngine/Globals.h"


EntityLiving::EntityLiving(): m_fCurrentHealth(0),
                              m_fMaxHealth(0),
                              m_iCurrentFrameIndex(0),
                              m_iLastFrameIndex(0),
                              m_fCurrentDelay(0),
                              m_iFrameCount(0),
                              m_pBody(nullptr),
                              m_fMaxSpeed(0),
                              m_fMovementSpeed(3)
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

	m_Sprite.SetPosition(position);
}

void EntityLiving::InitSprite(int modelId, int spriteSheetId, int shadersId)
{
	m_Sprite.SetModel(ResourceMgr->GetModelById(modelId));
	m_Sprite.SetTexture(ResourceMgr->GetSpriteSheetById(spriteSheetId));
	m_Sprite.SetShaders(ResourceMgr->GetShadersById(shadersId));
}

void EntityLiving::SetAnimations(std::vector<Animation*> animations)
{
	m_vecAnimations = animations;
}


Animation* EntityLiving::GetAnimation(int index)
{
	if (index >= m_vecAnimations.size())
	{
		return nullptr;
	}

	return m_vecAnimations.at(index);
}

void EntityLiving::UpdateAnimationToSprite(Animation* animation)
{
	if (m_iCurrentFrameIndex == m_iLastFrameIndex)
	{	// in duration of current frame, increase delay
		m_fCurrentDelay += Globals::animationTime * Globals::deltaTime;
	}
	else
	{	// into new frame
		m_iFrameCount++;
		m_fCurrentDelay = 0;
	}
	Frame* frame = animation->GetFrameByIndex(m_iCurrentFrameIndex);
	m_Sprite.SetFrame(frame);

	m_iLastFrameIndex = m_iCurrentFrameIndex;
	m_iCurrentFrameIndex = animation->GetNextFrameIndex(m_iCurrentFrameIndex, m_fCurrentDelay);
}

int EntityLiving::GetFrameCount() const
{
	return m_iFrameCount;
}

void EntityLiving::ResetCurrentAnimationInfo()
{
	m_iCurrentFrameIndex = 0;
	m_iLastFrameIndex = 0;
	m_fCurrentDelay = 0.0f;
	m_iFrameCount = 0;
}


void EntityLiving::SetSpriteData(int index, Vector2 position)
{
	m_Sprite.SetIndex(index);
	m_Sprite.SetPosition(position);
}

void EntityLiving::InitBody(b2BodyDef& bodyDef, b2FixtureDef& fixtureDef)
{
	m_pBody = PhysicsMgr->GetWorld()->CreateBody(&bodyDef);
	m_pBody->CreateFixture(&fixtureDef);
}

b2Body* EntityLiving::GetBody() const
{
	return m_pBody;
}

void EntityLiving::Reset()
{
}
