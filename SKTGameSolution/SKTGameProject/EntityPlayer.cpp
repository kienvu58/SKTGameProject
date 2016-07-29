#include "EntityPlayer.h"
#include "GamePlayState.h"
#include "SingletonClasses.h"


EntityPlayer::EntityPlayer(): m_fMaxKi(0), m_fCurrentKi(0), m_pStateMachine(new StateMachine<EntityPlayer>(this))
{
	m_pStateMachine->SetGlobalState(PS_Global::GetInstance());
	m_pStateMachine->SetCurrentState(PS_Standing::GetInstance());
}


EntityPlayer::~EntityPlayer()
{
	delete m_pStateMachine;
}

void EntityPlayer::Render()
{
	m_Sprite.Render();
}

void EntityPlayer::Update()
{
	EntityLiving::Update();
	m_pStateMachine->Update();
}

EntityType EntityPlayer::GetType()
{
	return ENTITY_PLAYER;
}

bool EntityPlayer::HandleMessage(const Telegram& telegram)
{
	return false;
}

StateMachine<EntityPlayer>* EntityPlayer::GetFSM() const
{
	return m_pStateMachine;
}

EntityLiving* EntityPlayer::Clone()
{
	return nullptr;
}
