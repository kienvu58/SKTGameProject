#include "GameOptionState.h"
#include "GameWelcomeState.h"
#include "MainMenuState.h"


GameOptionState::GameOptionState()
{
}

void GameOptionState::Enter(Game* game)
{

}

void GameOptionState::Execute(Game* game)
{
	m_Background->Update();
	if (InputMgr->GetLastMousePosition().x >= 430.0f && InputMgr->GetLastMousePosition().x <= 500.0f
		&& InputMgr->GetLastMousePosition().y >= 290.0f && InputMgr->GetLastMousePosition().y <= 340.0f)
	{
		game->GetFSM()->ChangeState(MainMenuState ::GetInstance());
	}
}

void GameOptionState::Exit(Game* game)
{
}

void GameOptionState::Render(Game* game)
{
	m_Background->Render();
}

GameOptionState* GameOptionState::GetInstance()
{
	static GameOptionState instance;
	return &instance;
}

void GameOptionState::Clear()
{
	delete m_Background;
}

void GameOptionState::Init(const char* filePath)
{
	m_Background = new EntityStatic();
	m_Background->InitSprite(2, 35, 1);
}

GameOptionState::~GameOptionState()
{
}
