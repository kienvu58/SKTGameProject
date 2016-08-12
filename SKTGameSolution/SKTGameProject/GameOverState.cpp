#include "GameOverState.h"
#include "SingletonClasses.h"
#include "GamePlayState.h"

GameOverState::GameOverState()
{
}

void GameOverState::Enter(Game* game)
{
}

void GameOverState::PressButton(Game * game)
{
	if (game->GetFSM()->CurrentState() == GS_GameOver::GetInstance())
	{
		if (InputMgr->GetLastMousePosition().x >= 350 - 100 && InputMgr->GetLastMousePosition().x <= 350 + 100
			&& InputMgr->GetLastMousePosition().y >= 350 - 35 && InputMgr->GetLastMousePosition().y <= 350 + 35)
		{
			//YES (GAME PLAY)]
			GameInstance->Reset();
			GameInstance->GetFSM()->ChangeState(GS_GamePlay::GetInstance());
			InputMgr->SetLastMousePosition(0, 0);
//			GameInstance->GetFSM()->SetCurrentState(GS_GamePlay::GetInstance());
//					game->GetFSM()->ChangeState(GS_GamePlay::GetInstance());
			MusicMgr->MusicPlay("GamePlay");
			MusicMgr->MusicLoop("GamePlay");
		}
		if (InputMgr->GetLastMousePosition().x >= 750 - 100 && InputMgr->GetLastMousePosition().x <= 750 + 100
			&& InputMgr->GetLastMousePosition().y >= 350 - 35 && InputMgr->GetLastMousePosition().y <= 350 + 35)
		{
			//NO (BACK MAIN MENU)
			InputMgr->SetLastMousePosition(0, 0);
			GameInstance->Reset();
			GameInstance->GetFSM()->SetCurrentState(GS_MainMenu::GetInstance());
			MusicMgr->MusicPlay("MainMenu");
			MusicMgr->MusicLoop("MainMenu");
		}
	}
}

void GameOverState::Execute(Game* game)
{
	m_Background->Update();
	m_Button_Yes->Update();
	m_Button_No->Update();
	PressButton(game);
	std::cout << "SCOR: " << GS_GamePlay::GetInstance()->GetCurrentScore() << std::endl;
//	GPS->GetCurrentScore();
}

void GameOverState::Exit(Game* game)
{
}

void GameOverState::Render(Game* game)
{
	m_Background->Render();
	m_Button_Yes->Render();
	m_Button_No->Render();
}

void GameOverState::Init(const char* filePath)
{
	m_Background = new EntityStatic();
	m_Background->InitSprite(2, 102, 1);

	m_Button_Yes = new EntityStatic();
	m_Button_Yes->InitSprite(103, 206, 1);
	m_Button_Yes->InitPosition(350, 350);

	m_Button_No = new EntityStatic();
	m_Button_No->InitSprite(103, 205, 1);
	m_Button_No->InitPosition(750, 350);
}

bool GameOverState::OnMessage(Game*, const Telegram&)
{
	return false;
}

GameOverState::~GameOverState()
{
	delete m_Background;
	delete m_Button_Yes;
	delete m_Button_No;
	delete GPS;
}
