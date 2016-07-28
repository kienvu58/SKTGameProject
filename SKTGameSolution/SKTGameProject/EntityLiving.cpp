#include "EntityLiving.h"
#include "../GraphicsEngine/ResourceManager.h"
#include "PhysicsManager.h"
#include <Box2D/Dynamics/b2Fixture.h>
#include <ostream>
#include <iostream>
#include "../GraphicsEngine/Globals.h"


EntityLiving::EntityLiving(): m_fCurrentHealth(0),
                              m_fMaxHealth(0),
                              m_iCurrentFrame(0),
                              m_iLastFrame(0),
                              m_fCurrentDelay(0),
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


void EntityLiving::SetFrameToSprite(Frame* frame)
{
	m_Sprite.SetTexture(ResourceMgr->GetSpriteSheetById(frame->GetSpriteSheetId()));
	m_Sprite.SetIndex(frame->GetIndex());
}

Animation* EntityLiving::GetAnimation(int index)
{
	if (index >= m_vecAnimations.size())
	{
		return nullptr;
	}

	return m_vecAnimations.at(index);
}

void EntityLiving::ResetFramesInfo()
{
	m_iCurrentFrame = 0;
	m_iLastFrame = 0;
	m_fCurrentDelay = 0.0f;
}

void EntityLiving::SetCurrentFrame(int currentFrame)
{
	m_iLastFrame = m_iCurrentFrame;
	m_iCurrentFrame = currentFrame;
}

float EntityLiving::GetCurrentDelay() const
{
	return m_fCurrentDelay;
}

int EntityLiving::GetCurrentFrame() const
{
	return m_iCurrentFrame;
}

void EntityLiving::UpdateAnimationDelay()
{
	if (m_iCurrentFrame == m_iLastFrame)
	{
		m_fCurrentDelay += Globals::animationTime * Globals::deltaTime;
	}
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
