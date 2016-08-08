#include "EntityMinion.h"
#include <Box2D/Dynamics/b2Fixture.h>
#include <iostream>
#include "SingletonClasses.h"


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

EntityMinion::EntityMinion():m_fMaxForce(2)
{
	m_pSteeringBehavior = new SteeringBehavior(this);
}

EntityMinion::~EntityMinion()
{
	delete m_pSteeringBehavior;
}

float EntityMinion::GetMaxForce()
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

void EntityMinion::TruncateVelocity(b2Vec2& currentVelocity)
{
	if(currentVelocity.Length() > m_fMaxSpeed)
	{
		currentVelocity.Normalize();
		currentVelocity *= m_fMaxSpeed;
	}
}
