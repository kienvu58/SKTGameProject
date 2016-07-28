#include "GameWelcomeState.h"



GameWelcomeState::GameWelcomeState()
{
}

void GameWelcomeState::Enter(Game* game)
{

}

void GameWelcomeState::Execute(Game* game)
{
	m_Background->Update();
	Sleep(1500);
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
	m_Background = new EntityPlayer();
	m_Background->InitSprite(1, 1, 1);
}

GameWelcomeState::~GameWelcomeState()
{
}
