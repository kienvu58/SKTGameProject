#include "EntityPlayer.h"
#include "GamePlayState.h"
#include "SingletonClasses.h"


EntityPlayer::EntityPlayer(): m_fMaxKi(0),
                              m_fCurrentKi(0),
                              m_pStateMachine(new StateMachine<EntityPlayer>(this)),
                              m_iCurrentScore(0)
{
	m_fCurrentHealth = 100;
	m_fMaxHealth = 100;
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
	return m_pStateMachine->HandleMessage(telegram);
}

StateMachine<EntityPlayer>* EntityPlayer::GetFSM() const
{
	return m_pStateMachine;
}

EntityLiving* EntityPlayer::Clone()
{
	return nullptr;
}

void EntityPlayer::IncreseScore(int amout)
{
	m_iCurrentScore += amout;
}

int EntityPlayer::GetCurrentScore() const
{
	return m_iCurrentScore;
}
