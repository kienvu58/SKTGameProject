#include "GamePauseState.h"
#include "GamePlayState.h"
#include "SingletonClasses.h"

GamePauseState::GamePauseState(): m_Background(nullptr), m_Button_Resume(nullptr), m_Button_Quit(nullptr)
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

void GamePauseState::PressButton(Game* game) const
{
	Vector2 lastMousePosition = InputMgr->GetLastMousePosition();
	if (m_Button_Resume->IsClicked(lastMousePosition))
	{
		//Resum
		InputMgr->SetLastMousePosition(0, 0);
		game->GetFSM()->ChangeState(GS_GamePlay::GetInstance());
		MusicMgr->MusicPlay("GamePlay");
		MusicMgr->MusicLoop("GamePlay");
	}
//	if (InputMgr->GetLastMousePosition().x >= 785.0f && InputMgr->GetLastMousePosition().x <= 915.0f
//		&& InputMgr->GetLastMousePosition().y >= 195.0f && InputMgr->GetLastMousePosition().y <= 225.0f)
//	{
//		//Quit (back main menu)
//		MusicMgr->MusicPlay("MainMenu");
//		MusicMgr->MusicLoop("MainMenu");
//	}

	if (m_Button_Quit->IsClicked(lastMousePosition))
	{
		//Quit (back main menu)
//		GameInstance->DestroyStateInstances();
//		GameSingleton::DestroyInstance();
//
//		GameSingleton::CreateInstance();
//
//		GameInstance->CreateStateInstances();
		InputMgr->SetLastMousePosition(0, 0);
		GameInstance->Reset();
		GameInstance->GetFSM()->SetCurrentState(GS_MainMenu::GetInstance());
//		GameInstance->Init();
	}
}

void GamePauseState::Execute(Game* game)
{
	m_Background->Update();
	m_Button_Resume->Update();
	m_Button_Quit->Update();
	PressButton(game);
	//	printf("%f | %f \n", InputMgr->GetLastMousePosition().x, InputMgr->GetLastMousePosition().y);
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
	m_Background->InitSprite(2, 105, 1);

	m_Button_Resume = new EntityStatic();
	m_Button_Resume->InitSprite(6, 113, 1);
	m_Button_Resume->InitPosition(830, 162);

	m_Button_Quit = new EntityStatic();
	m_Button_Quit->InitSprite(7, 114, 1);
	m_Button_Quit->InitPosition(830, 210);
}

bool GamePauseState::OnMessage(Game*, const Telegram&)
{
	return false;
}
