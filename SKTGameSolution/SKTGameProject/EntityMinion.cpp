#include "EntityMinion.h"
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>


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

	force *= 0.2;
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
	return false;
}

StateMachine<EntityMinion>* EntityMinion::GetFSM() const
{
	return m_pStateMachine;
}

EntityMinion::EntityMinion():m_fMaxForce(4)
{
	m_pStateMachine = new StateMachine<EntityMinion>(this);
	m_pSteeringBehavior = new SteeringBehavior(this);
	m_pSteeringBehavior->WanderOn();
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
	EntityMinion* cloneMinion = new EntityMinion();
	//graphic
	cloneMinion->SetSprite(this->m_Sprite);
	cloneMinion->SetAnimations(this->m_vecAnimations);
	cloneMinion->ReverseSprite(this->m_bIsReversed);

	//physics
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(5, 0);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(MetersFromPixels(128) / 2 / 2, MetersFromPixels(128) / 2 / 2);

	b2FixtureDef fixture;
	fixture.shape = &boxShape;
	fixture.restitution = 1.0f;
	cloneMinion->InitBody(bodyDef, fixture, b2Vec2(-2, 0));

	return cloneMinion;
}

void EntityMinion::TruncateVelocity(b2Vec2& currentVelocity)
{
	if(currentVelocity.Length() > m_fMaxSpeed)
	{
		currentVelocity.Normalize();
		currentVelocity *= m_fMaxSpeed;
	}
}
