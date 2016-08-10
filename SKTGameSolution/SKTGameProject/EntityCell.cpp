#include <json.hpp>
#include <fstream>
#include "EntityCell.h"
#include "SingletonClasses.h"

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

void EntityCell::Init(int prototypeId, const char* dataPath)
{
	m_iPrototypeId = prototypeId;

	std::ifstream fin(dataPath);
	nlohmann::json data(fin);
	fin.close();
}

Entity* EntityCell::Clone()
{
	EntityMinion* cloneMinion = new EntityCell(*this);
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

void EntityCell::Reset()
{
	EntityMinion::Reset();
	m_pStateMachine->ChangeState(CS_Wandering::GetInstance());
}
