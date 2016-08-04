#include "GamePauseState.h"
#include "GameWelcomeState.h"
#include <Windows.h>
#include "GameOptionState.h"
#include "GamePlayState.h"
#include "SingletonClasses.h"
#include "SoundManager.h"
GamePauseState::GamePauseState()
{
}


GamePauseState::~GamePauseState()
{
	delete m_Background;
	delete m_Button_Resume;
	delete m_Button_Quit;
}

void GamePauseState::Enter(Game* game)
{
}

void GamePauseState::Execute(Game* game)
{
	m_Background->Update();
	m_Button_Resume->Update();
	m_Button_Quit->Update();
	//	printf("%f | %f \n", InputMgr->GetLastMousePosition().x, InputMgr->GetLastMousePosition().y);
	if (InputMgr->GetLastMousePosition().x >= 765.0f && InputMgr->GetLastMousePosition().x <= 895.0f
		&& InputMgr->GetLastMousePosition().y >= 147.0f && InputMgr->GetLastMousePosition().y <= 177.0f)
	{
		//Resum
		game->GetFSM()->ChangeState(GS_GamePlay::GetInstance());
		MusicMgr->MusicPlay("GamePlay");
		MusicMgr->MusicLoop("GamePlay");
		MusicMgr->MusicVolume("GamePlay", 50);
	}
	if (InputMgr->GetLastMousePosition().x >= 785.0f && InputMgr->GetLastMousePosition().x <= 915.0f
		&& InputMgr->GetLastMousePosition().y >= 195.0f && InputMgr->GetLastMousePosition().y <= 225.0f)
	{
		//Quit (back main menu)
		GameInstance->DestroyStateInstances();
		GameSingleton::DestroyInstance();

		GameSingleton::CreateInstance();

		GameInstance->CreateStateInstances();
		GameInstance->GetFSM()->SetCurrentState(GS_MainMenu::GetInstance());
		GameInstance->Init();

		MusicMgr->MusicPlay("MainMenu");
		MusicMgr->MusicLoop("MainMenu");
	}
}

void GamePauseState::Exit(Game* game)
{
}

void GamePauseState::Render(Game* game)
{
	m_Background->Render();
	m_Button_Resume->Render();
	m_Button_Quit->Render();
}

void GamePauseState::Init(const char* filePath)
{

	m_Background = new EntityStatic();
	m_Background->InitSprite(2, 46, 1);

	m_Button_Resume = new EntityStatic();
	m_Button_Resume->InitSprite(6, 43, 1);
	m_Button_Resume->InitPosition(830, 162);

	m_Button_Quit = new EntityStatic();
	m_Button_Quit->InitSprite(7, 44, 1);
	m_Button_Quit->InitPosition(830, 210);
}

bool GamePauseState::OnMessage(Game*, const Telegram&)
{
	return false;
}
