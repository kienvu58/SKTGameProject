#include <json.hpp>
#include <fstream>
#include "GameOverState.h"
#include "SingletonClasses.h"
#include "GamePlayState.h"
#include "Definations.h"

GameOverState::GameOverState(): m_Background(nullptr), m_Button_Yes(nullptr), m_Button_No(nullptr), m_iBestScore(0)
{
}

void GameOverState::Enter(Game* game)
{
	auto dataPath = std::string(DATA_PATH);
	dataPath.append("BEST_SCORE.json");
	std::ifstream scoreFile(dataPath.c_str());
	std::ofstream outFile(dataPath.c_str());

	if (scoreFile.is_open())
	{
		float bestScore;
		scoreFile >> bestScore;
		float currentScore = GS_GamePlay::GetInstance()->GetCurrentScore();
		if (currentScore > bestScore)
		{
			outFile << currentScore;
			SetBestScore(currentScore);
		}
	}
	scoreFile.close();
	outFile.close();
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
}

void GameOverState::Exit(Game* game)
{
}

void GameOverState::Render(Game* game)
{
	m_Background->Render();
	m_Button_Yes->Render();
	m_Button_No->Render();

	std::string scoreText = "Best Score: ";
	scoreText.append(std::to_string(GetBestScore()));
	TextMgr->RenderString(scoreText.c_str(), Vector4(1, 0, 0, 1), 100.0f, 0, 0, 1, 1);
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
}

void GameOverState::SetBestScore(int s)
{
	m_iBestScore = s;
}

int GameOverState::GetBestScore() const
{
	return m_iBestScore;
}
