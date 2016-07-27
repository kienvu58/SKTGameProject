#include "EntityPlayer.h"
#include "PlayerStandingState.h"
#include "../GraphicsEngine/ResourceManager.h"
#include "../GraphicsEngine/AnimationManager.h"
#include "../GraphicsEngine/InputManager.h"
#include "GamePlayState.h"


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
	m_Sprite.Render();
}

void EntityPlayer::Update()
{
	EntityLiving::Update();

	auto keyA = InputMgr->IsPressed(KEY_A);
	auto keyD = InputMgr->IsPressed(KEY_D);
	auto keyW = InputMgr->IsPressed(KEY_W);
	auto keyS = InputMgr->IsPressed(KEY_S);

	m_pStateMachine->Update();
}


StateMachine<EntityPlayer>* EntityPlayer::GetFSM() const
{
	return m_pStateMachine;
}
