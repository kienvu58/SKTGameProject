#include "EntityPlayer.h"
#include "PlayerStandingState.h"
#include "../GraphicsEngine/ResourceManager.h"
#include "../GraphicsEngine/AnimationManager.h"


Animation* EntityPlayer::s_AnimationStanding = nullptr;
Animation* EntityPlayer::s_AnimationMovingForward = nullptr;
Animation* EntityPlayer::s_AnimationMovingBackward = nullptr;

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
	m_pStateMachine->Update();
}

void EntityPlayer::InitSprite(int modelId, int spriteSheetId, int shadersId)
{
	m_Sprite.SetModel(ResourceMgr->GetModelById(modelId));
	m_Sprite.SetTexture(ResourceMgr->GetSpriteSheetById(spriteSheetId));
	m_Sprite.SetShaders(ResourceMgr->GetShadersById(shadersId));
}


void EntityPlayer::InitAnimations(int animationStandingId, int animationMovingForwardId, int animationMovingBackwardId)
{
	s_AnimationStanding = AnimationMgr->GetAnimationById(animationStandingId);
	s_AnimationMovingForward = AnimationMgr->GetAnimationById(animationMovingForwardId);
	s_AnimationMovingBackward = AnimationMgr->GetAnimationById(animationMovingBackwardId);
}

void EntityPlayer::SetFrameToSprite(Frame* frame)
{
	m_Sprite.SetTexture(ResourceMgr->GetSpriteSheetById(frame->GetSpriteSheetId()));
	m_Sprite.SetIndex(frame->GetIndex());
}

StateMachine<EntityPlayer>* EntityPlayer::GetFSM() const
{
	return m_pStateMachine;
}
