#include "MainMenuState.h"



MainMenuState::MainMenuState()
{
}


MainMenuState::~MainMenuState()
{
}

void MainMenuState::Enter(Game* game)
{
}

void MainMenuState::Execute(Game* game)
{
}

void MainMenuState::Exit(Game* game)
{
}

void MainMenuState::Render(Game* game)
{
	m_Background->Render();
	//m_Button_PlayGame->Render();
}

MainMenuState* MainMenuState::GetInstance()
{
	static MainMenuState instance;
	return &instance;
}

void MainMenuState::Init(const char* filePath)
{
	m_Background = new EntityPlayer();
	m_Background->InitSprite(2, 2, 1);
	//m_Button_PlayGame = new EntityPlayer();
	//m_Button_PlayGame->InitSprite(3, 3, 1);
//	m_Button_PlayGame->InitSprite(1, 3, 1);

}

void MainMenuState::Clear()
{
	delete m_Background;
	//delete m_Button_PlayGame;
}
