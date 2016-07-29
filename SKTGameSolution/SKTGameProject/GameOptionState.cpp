#include "GameOptionState.h"
#include "GameWelcomeState.h"
#include "SingletonClasses.h"


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
		game->GetFSM()->ChangeState(GS_MainMenu::GetInstance());
	}
}

void GameOptionState::Exit(Game* game)
{
}

void GameOptionState::Render(Game* game)
{
	m_Background->Render();
}

void GameOptionState::Init(const char* filePath)
{
	m_Background = new EntityStatic();
	m_Background->InitSprite(2, 35, 1);
}

GameOptionState::~GameOptionState()
{
	delete m_Background;
}
