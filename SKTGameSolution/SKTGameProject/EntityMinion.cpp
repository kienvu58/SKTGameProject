#include "EntityMinion.h"


void EntityMinion::Render()
{
	m_Sprite.Render();
}

void EntityMinion::Update()
{
	EntityLiving::Update();
	m_pStateMachine->Update();
}

StateMachine<EntityMinion>* EntityMinion::GetFSM() const
{
	return m_pStateMachine;
}

EntityMinion::EntityMinion()
{
	m_pStateMachine = new StateMachine<EntityMinion>(this);
}

EntityMinion::~EntityMinion()
{
	delete m_pStateMachine;
}
