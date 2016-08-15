#include "MainMenuState.h"
#include "GameWelcomeState.h"
#include "GamePlayState.h"
#include "SingletonClasses.h"
#include "SoundManager.h"

extern void GameCleanUp();
MainMenuState::MainMenuState(): m_Background(nullptr), m_Button_PlayGame(nullptr), m_Button_Option(nullptr), m_Button_Exit(nullptr)
{
}


MainMenuState::~MainMenuState()
{
	delete m_Background;
	delete m_Button_PlayGame;
	delete m_Button_Option;
	delete m_Button_Exit;
	//	delete m_Hp_Bar_Outline;
}

void MainMenuState::Enter(Game* game)
{
}

void MainMenuState::PressButton(Game* game) const
{
	if (game->GetFSM()->CurrentState() == GS_MainMenu::GetInstance())
	{
////		printf("MainMenuState\n");
//		if (InputMgr->GetLastMousePosition().x >= 200.0f && InputMgr->GetLastMousePosition().x <= 400.0f
//			&& InputMgr->GetLastMousePosition().y >= 150.0f && InputMgr->GetLastMousePosition().y <= 250.0f)
//		{
////			printf("GamePlay\n");
//			MusicMgr->MusicStop("MainMenu");
//			game->GetFSM()->ChangeState(GS_GamePlay::GetInstance());
//			MusicMgr->MusicPlay("GamePlay");
//			MusicMgr->MusicLoop("GamePlay");
//		}
//		if (InputMgr->GetLastMousePosition().x >= 200.0f && InputMgr->GetLastMousePosition().x <= 400.0f
//			&& InputMgr->GetLastMousePosition().y >= 300.0f && InputMgr->GetLastMousePosition().y <= 400.0f)
//		{
//			InputMgr->SetLastMousePosition(0, 0);
//			MusicMgr->MusicStop("MainMenu");
////			printf("GameOption\n");
//			game->GetFSM()->ChangeState(GS_Option::GetInstance());
//			MusicMgr->MusicPlay("GamePlay");
//			MusicMgr->MusicLoop("GamePlay");
//		}
//		if (InputMgr->GetLastMousePosition().x >= 200.0f && InputMgr->GetLastMousePosition().x <= 400.0f
//			&& InputMgr->GetLastMousePosition().y >= 450.0f && InputMgr->GetLastMousePosition().y <= 550.0f)
//		{
//			MusicMgr->MusicStop("MainMenu");			
//#ifdef WIN32
//			HWND hWnd = FindWindow(nullptr, "SKT Game");
//			DestroyWindow(hWnd);
//#endif
//		}
		Vector2 lastMousePosition = InputMgr->GetLastMousePosition();

		std::cout << "Last mouse pos: " << lastMousePosition.x << " " << lastMousePosition.y << std::endl;

		if (m_Button_PlayGame->IsClicked(lastMousePosition))
		{
			InputMgr->SetLastMousePosition(0, 0);
			MusicMgr->MusicStop("MainMenu");
			game->GetFSM()->ChangeState(GS_GamePlay::GetInstance());
			MusicMgr->MusicPlay("GamePlay");
			MusicMgr->MusicLoop("GamePlay");
		}
		if (m_Button_Option->IsClicked(lastMousePosition))
		{
			InputMgr->SetLastMousePosition(0, 0);
			MusicMgr->MusicStop("MainMenu");
			game->GetFSM()->ChangeState(GS_Option::GetInstance());
			MusicMgr->MusicPlay("GamePlay");
			MusicMgr->MusicLoop("GamePlay");
		}
		if (m_Button_Exit->IsClicked(lastMousePosition))
		{
			MusicMgr->MusicStop("MainMenu");
#ifdef WIN32
			HWND hWnd = FindWindow(nullptr, "SKT Game");
			DestroyWindow(hWnd);
#endif
		}
	}
}

void MainMenuState::Execute(Game* game)
{
	m_Background->Update();
	m_Button_PlayGame->Update();
	m_Button_Option->Update();
	m_Button_Exit->Update();
	//	m_Hp_Bar_Outline->Update();
	PressButton(game);
}

void MainMenuState::Exit(Game* game)
{
}

void MainMenuState::Render(Game* game)
{
	m_Background->Render();
	m_Button_PlayGame->Render();
	m_Button_Option->Render();
	m_Button_Exit->Render();
	//	m_Hp_Bar_Outline->Render();
}

void MainMenuState::Init(const char* filePath)
{
	m_Background = new EntityStatic();
	m_Background->InitSprite(2, 101, 1);

	m_Button_PlayGame = new EntityStatic();
	m_Button_PlayGame->InitSprite(3, 108, 1);
	m_Button_PlayGame->InitPosition(300, 200);//

	m_Button_Option = new EntityStatic();
	m_Button_Option->InitSprite(3, 109, 1);
	m_Button_Option->InitPosition(300, 350);

	m_Button_Exit = new EntityStatic();
	m_Button_Exit->InitSprite(3, 110, 1);
	m_Button_Exit->InitPosition(300, 500);

	MusicMgr->MusicVolume("MainMenu", 50);
}

bool MainMenuState::OnMessage(Game*, const Telegram&)
{
	return false;
}
