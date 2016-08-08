#include "EntityCell.h"
#include "SingletonClasses.h"
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>

EntityCell::EntityCell()
{
	m_fAttackDamage = 10;
	m_fCurrentHealth = 30;
	m_fMaxHealth = 30;
	
	m_pSteeringBehavior->WanderOn();

	m_pStateMachine = new StateMachine<EntityCell>(this);
	m_pStateMachine->SetGlobalState(CS_Global::GetInstance());
	m_pStateMachine->SetCurrentState(CS_Wandering::GetInstance());
}

EntityCell::~EntityCell()
{
	delete m_pStateMachine;
}

StateMachine<EntityCell>* EntityCell::GetFSM() const
{
	return m_pStateMachine;
}

Entity* EntityCell::Clone()
{
	EntityMinion* cloneMinion = new EntityCell();
	//graphic
	cloneMinion->SetSprite(this->m_Sprite);
	cloneMinion->SetAnimations(this->m_vecAnimations);
	cloneMinion->ReverseSprite(this->m_bIsReversed);

	//physics
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(0, 0);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(MetersFromPixels(128) / 2 / 4, MetersFromPixels(128) / 2 / 4);

	b2FixtureDef fixture;
	fixture.shape = &boxShape;
	fixture.restitution = 1.0f;
	fixture.filter.categoryBits = CATEGORY_MINION;
	fixture.filter.maskBits = CATEGORY_PLAYER | CATEGORY_KI_BLAST;
	cloneMinion->InitBody(bodyDef, fixture, b2Vec2(-2, 0));
	cloneMinion->GetBody()->SetActive(false);

	return cloneMinion;
}

void EntityCell::Update()
{
	EntityMinion::Update();
	m_pStateMachine->Update();
}

bool EntityCell::HandleMessage(const Telegram& telegram)
{
	return m_pStateMachine->HandleMessage(telegram);
}

EntityType EntityCell::GetType()
{
	return ENTITY_CELL;
}

void EntityCell::Reset()
{
	EntityMinion::Reset();
	m_pStateMachine->ChangeState(CS_Wandering::GetInstance());
}
