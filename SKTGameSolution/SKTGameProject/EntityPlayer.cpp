#include "EntityPlayer.h"
#include "PlayerStandingState.h"
#include "../GraphicsEngine/ResourceManager.h"
#include "../GraphicsEngine/AnimationManager.h"
#include "../GraphicsEngine/InputManager.h"


EntityPlayer::EntityPlayer(): currentFrame(0), delay(0), m_pStateMachine(new StateMachine<EntityPlayer>(this)) 
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
	auto keyA = InputMgr->IsPressed(KEY_A);
	auto keyD = InputMgr->IsPressed(KEY_D);
	auto keyW = InputMgr->IsPressed(KEY_W);
	auto keyS = InputMgr->IsPressed(KEY_S);



	m_pStateMachine->Update();
}

void EntityPlayer::InitSprite(int modelId, int spriteSheetId, int shadersId)
{
	m_Sprite.SetModel(ResourceMgr->GetModelById(modelId));
	m_Sprite.SetTexture(ResourceMgr->GetSpriteSheetById(spriteSheetId));
	m_Sprite.SetShaders(ResourceMgr->GetShadersById(shadersId));
}

void EntityPlayer::InitAnimations(std::map<std::string, Animation*> mapAnimations)
{
	m_mapAnimations = mapAnimations;
}

void EntityPlayer::SetFrameToSprite(Frame* frame)
{
	m_Sprite.SetTexture(ResourceMgr->GetSpriteSheetById(frame->GetSpriteSheetId()));
	m_Sprite.SetIndex(frame->GetIndex());
}

Animation* EntityPlayer::GetAnimationByName(std::string name)
{
	auto it = m_mapAnimations.find(name);
	if (it == m_mapAnimations.end())
	{
		return nullptr;
	}
	return it->second;
}

StateMachine<EntityPlayer>* EntityPlayer::GetFSM() const
{
	return m_pStateMachine;
}
