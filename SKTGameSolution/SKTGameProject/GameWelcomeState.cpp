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

#ifdef WIN32
	Sleep(1000);
#endif

	game->GetFSM()->ChangeState(GS_MainMenu::GetInstance());
	MusicMgr->MusicPlay("MainMenu");
	MusicMgr->MusicLoop("MainMenu");
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
	MusicMgr->InitMusic("MainMenu", "../Resources/Sound/musicMainMenu.wav");
	MusicMgr->InitMusic("GamePlay", "../Resources/Sound/musicGamePlay.wav");
	MusicMgr->InitMusic("Skill", "../Resources/Sound/hamehameha.wav");
}

bool GameWelcomeState::OnMessage(Game*, const Telegram&)
{
	return false;
}

GameWelcomeState::~GameWelcomeState()
{
	delete m_Background;
}
