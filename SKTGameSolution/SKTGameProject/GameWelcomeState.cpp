#include "GameWelcomeState.h"
#include "MainMenuState.h"


GameWelcomeState::GameWelcomeState()
{
}

void GameWelcomeState::Enter(Game* game)
{

}

void GameWelcomeState::Execute(Game* game)
{
	m_Background->Update();
	Sleep(1000);
	game->GetFSM()->ChangeState(MainMenuState::GetInstance());
}

void GameWelcomeState::Exit(Game* game)
{

}

void GameWelcomeState::Render(Game* game)
{
	m_Background->Render();
}

GameWelcomeState* GameWelcomeState::GetInstance()
{
	static GameWelcomeState instance;
	return &instance;
}

void GameWelcomeState::Clear()
{
	delete m_Background;
}

void GameWelcomeState::Init(const char* filePath)
{
	m_Background = new EntityStatic();
	m_Background->InitSprite(2, 30, 1); 
}

GameWelcomeState::~GameWelcomeState()
{
}
