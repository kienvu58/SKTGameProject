#include "EntityMinion.h"
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include "../GraphicsEngine/Globals.h"
#include <iostream>
#include "SingletonClasses.h"


void EntityMinion::Render()
{
	m_Sprite.Render();
}

void EntityMinion::Update()
{
	EntityLiving::Update();
	m_pStateMachine->Update();

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

bool EntityMinion::HandleMessage(const Telegram& telegram)
{
	return m_pStateMachine->HandleMessage(telegram);
}

StateMachine<EntityMinion>* EntityMinion::GetFSM() const
{
	return m_pStateMachine;
}

EntityMinion::EntityMinion():m_fMaxForce(2)
{
	m_pStateMachine = new StateMachine<EntityMinion>(this);
	m_pSteeringBehavior = new SteeringBehavior(this);
}

EntityMinion::~EntityMinion()
{
	delete m_pStateMachine;
	delete m_pSteeringBehavior;
}

float EntityMinion::GetMaxForce()
{
	return m_fMaxForce;
}

Entity* EntityMinion::Clone()
{
	return nullptr;
}

void EntityMinion::TruncateVelocity(b2Vec2& currentVelocity)
{
	if(currentVelocity.Length() > m_fMaxSpeed)
	{
		currentVelocity.Normalize();
		currentVelocity *= m_fMaxSpeed;
	}
}
