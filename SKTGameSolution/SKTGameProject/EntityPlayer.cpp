#include "EntityPlayer.h"
#include "../GraphicsEngine/ResourceManager.h"
#include "../GraphicsEngine/AnimationManager.h"
#include "../GraphicsEngine/InputManager.h"
#include "GamePlayState.h"
#include "PlayerOwnedStates.h"


EntityPlayer::EntityPlayer(): m_fMaxKi(0), m_fCurrentKi(0), m_pStateMachine(new StateMachine<EntityPlayer>(this))
{
	m_pStateMachine->SetCurrentState(PlayerStandingState::GetInstance());
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

	bool keyA = InputMgr->IsPressed(KEY_A);
	bool keyD = InputMgr->IsPressed(KEY_D);
	bool keyW = InputMgr->IsPressed(KEY_W);
	bool keyS = InputMgr->IsPressed(KEY_S);

	b2Vec2 direction(keyD - keyA, keyW - keyS);
	m_pBody->SetLinearVelocity(m_fMovementSpeed * direction);


	m_pStateMachine->Update();
}


StateMachine<EntityPlayer>* EntityPlayer::GetFSM() const
{
	return m_pStateMachine;
}
