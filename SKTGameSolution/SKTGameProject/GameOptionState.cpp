#include "GameOptionState.h"
#include "GameWelcomeState.h"
#include "SingletonClasses.h"
#include "SoundManager.h"

GameOptionState::GameOptionState()
{
}

void GameOptionState::Enter(Game* game)
{
}

void GameOptionState::PressButton(Game* game)
{
	if (game->GetFSM()->CurrentState() == GS_Option::GetInstance())
	{
		//		printf("GameOptionState\n");
		if (InputMgr->GetLastMousePosition().x >= (460 - 40) && InputMgr->GetLastMousePosition().x <= (460 + 40)
			&& InputMgr->GetLastMousePosition().y >= (320 - 25) && InputMgr->GetLastMousePosition().y <= (320 + 25))
		{
			//			printf("X\n");
			MusicMgr->MusicVolume("GamePlay", 50);
			MusicMgr->MusicStop("GamePlay");
			m_MusicBarBlack->InitPosition(460, 230);

			game->GetFSM()->ChangeState(GS_MainMenu::GetInstance());
			MusicMgr->MusicPlay("MainMenu");
		}
		if (InputMgr->GetLastMousePosition().x >= (280 - 40) && InputMgr->GetLastMousePosition().x <= (280 + 40)
			&& InputMgr->GetLastMousePosition().y >= (320 - 25) && InputMgr->GetLastMousePosition().y <= (320 + 25))
		{
			//			printf("V\n");
			MusicMgr->MusicStop("GamePlay");
			InputMgr->SetLastMousePosition(0, 0);
			game->GetFSM()->ChangeState(GS_MainMenu::GetInstance());
			MusicMgr->MusicPlay("MainMenu");
		}

		//Press Volume Bar
		if (InputMgr->GetCurrentMousePosition().x >= (460 - 100 + 5) && InputMgr->GetCurrentMousePosition().x <= (460 + 100 - 5)
			&& InputMgr->GetCurrentMousePosition().y >= (230 - 12.5 + 5) && InputMgr->GetCurrentMousePosition().y <= (230 + 12.5 - 5)
			||
			InputMgr->GetLastMousePosition().x >= (460 - 100 + 5) && InputMgr->GetLastMousePosition().x <= (460 + 100 - 5)
			&& InputMgr->GetLastMousePosition().y >= (230 - 12.5 + 5) && InputMgr->GetLastMousePosition().y <= (230 + 12.5 - 5)
			)
		{
			MusicBarBlack.x = InputMgr->GetCurrentMousePosition().x;
			if (InputMgr->GetCurrentMousePosition().x <= 460 - 100 + 5)
			{
				m_MusicBarBlack->InitPosition(365, MusicBarBlack.y);
				MusicMgr->MusicVolume("GamePlay", 0);
			}
			else if (InputMgr->GetCurrentMousePosition().x >= 460 + 100 - 5)
			{
				m_MusicBarBlack->InitPosition(555, MusicBarBlack.y);
				MusicMgr->MusicVolume("GamePlay", 100);
			}
			else
			{
				m_MusicBarBlack->InitPosition(MusicBarBlack.x, MusicBarBlack.y);
				//printf("a: %f \n", 100-(565- MusicBarBlack.x)/2);
				MusicMgr->MusicVolume("GamePlay", 100 - (555 - MusicBarBlack.x) / 2);
			}
		}
	}
}

void GameOptionState::Execute(Game* game)
{
	m_Background->Update();
	m_Button_V->Update();
	m_Button_X->Update();
	m_MusicBarGreen->Update();
	m_MusicBarBlack->Update();
	PressButton(game);
	//	printf("%f | %f \n", InputMgr->GetCurrentMousePosition().x, InputMgr->GetCurrentMousePosition().y);
}

void GameOptionState::Exit(Game* game)
{
}

void GameOptionState::Render(Game* game)
{
	m_Background->Render();
	m_Button_V->Render();
	m_Button_X->Render();
	m_MusicBarGreen->Render();
	m_MusicBarBlack->Render();
}

void GameOptionState::Init(const char* filePath)
{
	m_Background = new EntityStatic();
	m_Background->InitSprite(2, 35, 1);

	m_Button_V = new EntityStatic();
	m_Button_V->InitSprite(9, 41, 1);
	m_Button_V->InitPosition(280, 320);

	m_Button_X = new EntityStatic();
	m_Button_X->InitSprite(9, 42, 1);
	m_Button_X->InitPosition(460, 320);

	m_MusicBarGreen = new EntityStatic();
	m_MusicBarGreen->InitSprite(10, 51, 1);
	m_MusicBarGreen->InitPosition(460, 230);

	m_MusicBarBlack = new EntityStatic();
	m_MusicBarBlack->InitSprite(11, 52, 1);
	m_MusicBarBlack->InitPosition(460, 230);

	MusicBarBlack.x = 460;
	MusicBarBlack.y = 230;
}

bool GameOptionState::OnMessage(Game*, const Telegram&)
{
	return false;
}

GameOptionState::~GameOptionState()
{
	delete m_Background;
	delete m_Button_V;
	delete m_Button_X;
	delete m_MusicBarGreen;
	delete m_MusicBarBlack;
}
