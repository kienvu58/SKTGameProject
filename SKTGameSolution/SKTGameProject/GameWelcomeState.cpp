#include "GameWelcomeState.h"
#include "SingletonClasses.h"

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
	game->GetFSM()->ChangeState(GS_MainMenu::GetInstance());
}

void GameWelcomeState::Exit(Game* game)
{
}

void GameWelcomeState::Render(Game* game)
{
	m_Background->Render();
}

void GameWelcomeState::Init(const char* filePath)
{
	m_Background = new EntityStatic();
	m_Background->InitSprite(2, 30, 1); 
}

bool GameWelcomeState::OnMessage(Game*, const Telegram&)
{
	return false;
}

GameWelcomeState::~GameWelcomeState()
{
	delete m_Background;
}
