#include "EntityCellJunior.h"
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include "SingletonClasses.h"


EntityCellJunior::EntityCellJunior()
{
	m_pSteeringBehavior->WanderOn();
//	m_pSteeringBehavior->SeekOn();
	m_pStateMachine = new StateMachine<EntityCellJunior>(this);
	m_pStateMachine->SetCurrentState(CJS_Wandering::GetInstance());
	m_pStateMachine->SetGlobalState(CJS_Global::GetInstance());
}

EntityCellJunior::~EntityCellJunior()
{
	delete m_pStateMachine;
}

StateMachine<EntityCellJunior>* EntityCellJunior::GetFSM() const
{
	return m_pStateMachine;
}

Entity* EntityCellJunior::Clone()
{
	EntityMinion* cloneMinion = new EntityCellJunior();
	//graphic
	cloneMinion->SetSprite(this->m_Sprite);
	cloneMinion->SetAnimations(this->m_vecAnimations);
	cloneMinion->ReverseSprite(this->m_bIsReversed);

	//physics
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(0, 0);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(MetersFromPixels(128) / 2 / 2, MetersFromPixels(128) / 2 / 2);

	b2FixtureDef fixture;
	fixture.shape = &boxShape;
	fixture.restitution = 1.0f;
	fixture.filter.groupIndex = -1;
	cloneMinion->InitBody(bodyDef, fixture, b2Vec2(-2, 0));

	return cloneMinion;
}

void EntityCellJunior::Update()
{
	EntityMinion::Update();
	m_pStateMachine->Update();
}

bool EntityCellJunior::HandleMessage(const Telegram& telegram)
{
	return m_pStateMachine->HandleMessage(telegram);
}
