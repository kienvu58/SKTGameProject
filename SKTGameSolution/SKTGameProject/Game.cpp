#include "Game.h"
#include "GamePlayState.h"
#include "MainMenuState.h"
#include "GameWelcomeState.h"
#include <Windows.h>
#include "SingletonClasses.h"

Game::Game(): m_pStateMachine(new StateMachine<Game>(this))
{
}

Game::~Game()
{
	delete m_pStateMachine;
}

void Game::Init()
{
	GS_Welcome::GetInstance()->Init("");
	GS_MainMenu::GetInstance()->Init("");
	GS_GamePlay::GetInstance()->Init("");
}

void Game::CreateStateInstances()
{
	GS_Welcome::CreateInstance();
	GS_MainMenu::CreateInstance();
	GS_GamePlay::CreateInstance();

	PS_Global::CreateInstance();
	PS_Firing::CreateInstance();
	PS_Moving::CreateInstance();
	PS_Standing::CreateInstance();

	MS_Wandering::CreateInstance();
}

void Game::DestroyStateInstances()
{
	GS_Welcome::DestroyInstance();
	GS_MainMenu::DestroyInstance();
	GS_GamePlay::DestroyInstance();

	PS_Global::DestroyInstance();
	PS_Firing::DestroyInstance();
	PS_Moving::DestroyInstance();
	PS_Standing::DestroyInstance();

	MS_Wandering::DestroyInstance();
}

void Game::Update()
{
	m_pStateMachine->Update();
}

void Game::Render()
{
	m_pStateMachine->Render();
}

StateMachine<Game>* Game::GetFSM() const
{
	return m_pStateMachine;
}
