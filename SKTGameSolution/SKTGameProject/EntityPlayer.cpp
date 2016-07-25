#include "EntityPlayer.h"
#include "PlayerStandingState.h"


EntityPlayer::EntityPlayer(): m_pStateMachine(new StateMachine<EntityPlayer>(this)) 
{
	m_pStateMachine->SetCurrentState(PlayerStandingState::GetInstance());
}


EntityPlayer::~EntityPlayer()
{
	delete m_pStateMachine;
}

void EntityPlayer::Render()
{
	m_pStateMachine->Render();
}

void EntityPlayer::Update()
{
	m_pStateMachine->Update();
}
