#include "EntityMinion.h"
#include <Box2D/Dynamics/b2Fixture.h>
#include "SingletonClasses.h"
#include "EntityEffect.h"


EntityMinion::EntityMinion() : m_pSteeringBehavior(nullptr), m_fMaxForce(2), m_iExplosionPID(0), m_iPrize(10)
{
}

void EntityMinion::Render()
{
	m_Sprite.Render();
}

void EntityMinion::Update()
{
	EntityLiving::Update();

	b2Vec2 force = m_pSteeringBehavior->Calculate();
	b2Vec2 currentVelocity = m_pBody->GetLinearVelocity();

	currentVelocity += force;
	TruncateVelocity(currentVelocity);

	m_pBody->SetLinearVelocity(currentVelocity);
}

EntityType EntityMinion::GetType()
{
	return ENTITY_MINION;
}

void EntityMinion::InitSteeringBehavior()
{
	m_pSteeringBehavior = new SteeringBehavior(this);
}

EntityMinion::~EntityMinion()
{
	if (m_pSteeringBehavior)
		delete m_pSteeringBehavior;
}

float EntityMinion::GetMaxForce() const
{
	return m_fMaxForce;
}

SteeringBehavior* EntityMinion::GetSteering() const
{
	return m_pSteeringBehavior;
}

Entity* EntityMinion::Clone()
{
	return nullptr;
}

void EntityMinion::Reset()
{
	EntityLiving::Reset();
}

void EntityMinion::Explode()
{
	auto explosionEffect = static_cast<EntityEffect*>(PoolMgr->GetEntityByPrototypeId(m_iExplosionPID));
	auto explosionPos = m_pBody->GetPosition();
	explosionEffect->Start(explosionPos, GameInstance);
	GS_GamePlay::GetInstance()->AddEntityToTheScreen(explosionEffect);

	m_bIsActive = false;
}

int EntityMinion::GetPrize() const
{
	return m_iPrize;
}

void EntityMinion::TruncateVelocity(b2Vec2& currentVelocity) const
{
	if (currentVelocity.Length() > m_fMaxSpeed)
	{
		currentVelocity.Normalize();
		currentVelocity *= m_fMaxSpeed;
	}
}
