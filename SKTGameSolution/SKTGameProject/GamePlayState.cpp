#include "GamePlayState.h"
#include "../GraphicsEngine/ResourceManager.h"
#include "../GraphicsEngine/AnimationManager.h"
#include "../GraphicsEngine/FrameManager.h"
#include "../GraphicsEngine/TextManager.h"

static Sprite spriteGoku;

GamePlayState::GamePlayState()
{
}

void GamePlayState::Enter(Game* game)
{

}

void GamePlayState::Execute(Game* game)
{
	m_Background->Update();
	m_Goku->Update();
	m_pButton->Update();
}

void GamePlayState::Exit(Game* game)
{
}

void GamePlayState::Render(Game* game)
{
	m_Background->Render();
	m_Goku->Render();
	TextMgr->RenderString("Test Game", Vector4(1, 0, 0, 1), 60.0f, 0, 0, 1, 1);
	m_pButton->Render();
}

GamePlayState* GamePlayState::GetInstance()
{
	static GamePlayState instance;
	return &instance;
}

void GamePlayState::Clear()
{
	delete m_Background;
	delete m_Goku;
	delete m_pButton;
}

void GamePlayState::Init(const char* filePath)
{
	m_Goku = new EntityPlayer();
	m_Goku->InitSprite(1, 1, 1);
	m_Background = new EntityPlayer();
	m_Background->InitSprite(2, 2, 1);
	m_pButton = new EntityPlayer();
	m_pButton->InitSprite(3, 3, 1);
}

GamePlayState::~GamePlayState()
{
}
