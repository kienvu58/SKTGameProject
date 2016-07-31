#include "EntityLiving.h"
#include "PhysicsManager.h"
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/b2World.h>
#include <ostream>
#include "../GraphicsEngine/Globals.h"
#include "SingletonClasses.h"


EntityLiving::EntityLiving(): m_fCurrentHealth(50),
                              m_fMaxHealth(50),
                              m_bIsReversed(false),
                              m_iCurrentFrameIndex(0),
                              m_iLastFrameIndex(0),
                              m_fCurrentDelay(0),
                              m_iFrameCount(0),
                              m_pBody(nullptr),
                              m_fMaxSpeed(4),
                              m_fMovementSpeed(3)
{
}


EntityLiving::~EntityLiving()
{
}

void EntityLiving::Update()
{
	m_Sprite.SetRenderInfo(GraphicsFromPhysics(m_pBody->GetPosition()), m_bIsReversed);
}

EntityType EntityLiving::GetType()
{
	return ENTITY_LIVING;
}

void EntityLiving::InitSprite(int modelId, int frameId, int shaderId)
{
	m_Sprite.SetModel(ResourceMgr->GetModelById(modelId));
	m_Sprite.SetFrame(FrameMgr->GetFrameById(frameId));
	m_Sprite.SetShaders(ResourceMgr->GetShadersById(shaderId));
}

void EntityLiving::SetSprite(Sprite sprite)
{
	this->m_Sprite = sprite;
}

void EntityLiving::ReverseSprite(bool isReversed)
{
	m_bIsReversed = isReversed;
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
	{ // in duration of current frame, increase delay
		m_fCurrentDelay += Globals::animationTime * Globals::deltaTime;
	}
	else
	{ // into new frame
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

bool EntityLiving::IsFrameChanged() const
{
	return !(m_iCurrentFrameIndex == m_iLastFrameIndex);
}

void EntityLiving::InitBody(const b2BodyDef& bodyDef, const b2FixtureDef& fixtureDef, b2Vec2 velocity)
{
	m_pBody = PhysicsMgr->GetWorld()->CreateBody(&bodyDef);
	m_pBody->CreateFixture(&fixtureDef);
	m_pBody->SetLinearVelocity(velocity);
	m_pBody->SetUserData(this);
}

b2Body* EntityLiving::GetBody() const
{
	return m_pBody;
}

float EntityLiving::GetMaxSpeed() const
{
	return m_fMaxSpeed;
}

void EntityLiving::SetBody(b2Body* body)
{
}

float EntityLiving::GetMovementSpeed() const
{
	return m_fMovementSpeed;
}

void EntityLiving::Reset()
{
}
