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
}

MainMenuState* MainMenuState::GetInstance()
{
	static MainMenuState instance;
	return &instance;
}
