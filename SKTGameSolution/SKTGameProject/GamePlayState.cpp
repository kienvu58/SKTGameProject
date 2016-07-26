#include "GamePlayState.h"
#include "../GraphicsEngine/ResourceManager.h"
#include "../GraphicsEngine/AnimationManager.h"
#include "../GraphicsEngine/FrameManager.h"

static Sprite spriteGoku;

GamePlayState::GamePlayState()
{
}

void GamePlayState::Enter(Game* game)
{
	ResourceMgr->Init("../Resources/Data/RM.json");
	FrameMgr->Init("../Resources/Data/FM.json");
	AnimationMgr->Init("../Resources/Data/AM.json");
	m_Goku.InitSprite(1, 1, 1);
	m_Goku.InitAnimations(1, 2, 3);
}

void GamePlayState::Execute(Game* game)
{
	m_Goku.Update();
}

void GamePlayState::Exit(Game* game)
{
}

void GamePlayState::Render(Game* game)
{
	m_Goku.Render();
}

GamePlayState* GamePlayState::GetInstance()
{
	static GamePlayState instance;
	return &instance;
}

GamePlayState::~GamePlayState()
{
}
