#include "EntityLiving.h"
#include "PhysicsManager.h"
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/b2World.h>
#include <ostream>
#include "../GraphicsEngine/Globals.h"
#include "SingletonClasses.h"


EntityLiving::EntityLiving(): m_fCurrentHealth(50),
                              m_fMaxHealth(50),
                              m_fCurrentOverHeat(0),
                              m_bIsOverheated(false),
                              m_fAttackDamage(0),
                              m_bIsReversed(false),
                              m_iCurrentFrameIndex(0),
                              m_iLastFrameIndex(0),
                              m_fCurrentDelay(0),
                              m_iFrameCount(0),
                              m_pBody(nullptr),
                              m_fMaxSpeed(10),
                              m_fMovementSpeed(3)
{
}

EntityLiving::EntityLiving(const EntityLiving& entityLiving): m_fCurrentHealth(entityLiving.m_fMaxHealth),
                                                              m_fMaxHealth(entityLiving.m_fMaxHealth),
                                                              m_fCurrentOverHeat(0), m_bIsOverheated(false),
                                                              m_fAttackDamage(entityLiving.m_fAttackDamage),
                                                              m_Sprite(entityLiving.m_Sprite),
                                                              m_bIsReversed(entityLiving.m_bIsReversed),
                                                              m_vecAnimations(entityLiving.m_vecAnimations),
                                                              m_iCurrentFrameIndex(0),
                                                              m_iLastFrameIndex(0),
                                                              m_fCurrentDelay(0),
                                                              m_iFrameCount(0),
                                                              m_fMaxSpeed(entityLiving.m_fMaxSpeed),
                                                              m_fMovementSpeed(entityLiving.m_fMovementSpeed),
                                                              m_b2PolygonShape(entityLiving.m_b2PolygonShape),
                                                              m_b2BodyDef(entityLiving.m_b2BodyDef),
                                                              m_b2FixtureDef(entityLiving.m_b2FixtureDef)
{
	m_iPrototypeId = entityLiving.m_iPrototypeId;
	InitBody(m_b2BodyDef, m_b2FixtureDef);
	m_pBody->SetUserData(this);
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

void EntityLiving::UpdateSpriteFrame(Animation* animation)
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
	auto frame = animation->GetFrameByIndex(m_iCurrentFrameIndex);
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

void EntityLiving::ScaleVelocity(int scale) const
{
	b2Vec2 currentVelocity = m_pBody->GetLinearVelocity();
	currentVelocity *= scale;
	m_pBody->SetLinearVelocity(currentVelocity);
}

float EntityLiving::GetAttackDamage() const
{
	return m_fAttackDamage;
}

float EntityLiving::GetMaxHealth() const
{
	return m_fMaxHealth;
}

float EntityLiving::GetMovementSpeed() const
{
	return m_fMovementSpeed;
}

void EntityLiving::IncreaseOverheat(float amount)
{
	m_fCurrentOverHeat += amount;
	if (m_fCurrentOverHeat >= MAX_OVERHEAT)
	{
		m_fCurrentOverHeat = MAX_OVERHEAT;
		m_bIsOverheated = true;
	}
}

float EntityLiving::GetCurrentOverheat() const
{
	return m_fCurrentOverHeat;
}

void EntityLiving::DecreaseOverheatPerSecond(float amount)
{
	m_fCurrentOverHeat -= amount * Globals::deltaTime;
	if (m_fCurrentOverHeat <= MIN_OVERHEAT)
	{
		m_fCurrentOverHeat = MIN_OVERHEAT;
		m_bIsOverheated = false;
	}
}

bool EntityLiving::IsOverheated() const
{
	return m_bIsOverheated;
}

void EntityLiving::SetOverheat(float value)
{
	m_fCurrentOverHeat = value;
}

void EntityLiving::Reset()
{
	m_fCurrentHealth = m_fMaxHealth;
	m_fCurrentOverHeat = MIN_OVERHEAT;
	m_bIsActive = false;
	m_pBody->SetActive(false);
}

bool EntityLiving::IsOutOfWall() const
{
	float padding = 2;
	float wallHalfWidth = MetersFromPixels(Globals::screenWidth) / 2;
	float wallHalfHeight = MetersFromPixels(Globals::screenHeight) / 2;
	float boundryX = wallHalfWidth + padding;
	float boundryY = wallHalfHeight + padding;
	
	b2Vec2 position = m_pBody->GetPosition();

	if (-boundryX < position.x && position.x < boundryX + 3
		&& -boundryY < position.y && position.y < boundryY)
		return false;

	return true;
}

void EntityLiving::TakeDamage(float amount)
{
	m_fCurrentHealth -= amount;
	if (m_fCurrentHealth <= 0)
	{
		m_fCurrentHealth = 0;
	}
}

bool EntityLiving::IsDead() const
{
	if (m_fCurrentHealth == 0)
		return true;
	return false;
}

float EntityLiving::GetCurrentHealth() const
{
	return m_fCurrentHealth;
}

void EntityLiving::Activate()
{
	m_bIsActive = true;
	m_pBody->SetActive(true);
}
