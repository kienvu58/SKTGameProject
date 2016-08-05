#include "EntityPlayer.h"
#include "GamePlayState.h"
#include "SingletonClasses.h"
#include "../GraphicsEngine/Globals.h"


EntityPlayer::EntityPlayer(): m_fMaxKi(0),
                              m_fCurrentKi(0),
                              m_iCurrentScore(0),
                              m_pStateMachine(new StateMachine<EntityPlayer>(this))
{
	m_fCurrentHealth = 10;
	m_fMaxHealth = 10;
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

void EntityPlayer::IncreseScore(int amount)
{
	m_iCurrentScore += amount;
}

int EntityPlayer::GetCurrentScore() const
{
	return m_iCurrentScore;
}

bool EntityPlayer::IsOnTheGround() const
{
	b2Vec2 currentPosition = m_pBody->GetPosition();
	float groudY = MetersFromPixels(Globals::screenHeight / 2);
	if (currentPosition.y <= -(groudY + 1))
		return true;
	return false;
}
