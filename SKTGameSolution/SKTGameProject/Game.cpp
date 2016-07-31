#include "Game.h"
#include "GamePlayState.h"
#include "MainMenuState.h"
#include "GameWelcomeState.h"
#include <Windows.h>
#include "GameOptionState.h"
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
	GS_Option::GetInstance()->Init("");
}

void Game::CreateStateInstances()
{
	GS_Welcome::CreateInstance();
	GS_MainMenu::CreateInstance();
	GS_GamePlay::CreateInstance();
	GS_Option::CreateInstance();

	PS_Global::CreateInstance();
	PS_Firing::CreateInstance();
	PS_Moving::CreateInstance();
	PS_Standing::CreateInstance();
	PS_FiringSpecial::CreateInstance();
	PS_FiringUltimate::CreateInstance();

	MS_Wandering::CreateInstance();
	MS_Global::CreateInstance();
}

void Game::DestroyStateInstances()
{
	GS_Welcome::DestroyInstance();
	GS_MainMenu::DestroyInstance();
	GS_GamePlay::DestroyInstance();
	GS_Option::DestroyInstance();

	PS_Global::DestroyInstance();
	PS_Firing::DestroyInstance();
	PS_Moving::DestroyInstance();
	PS_Standing::DestroyInstance();
	PS_FiringSpecial::DestroyInstance();
	PS_FiringUltimate::DestroyInstance();

	MS_Wandering::DestroyInstance();
	MS_Global::DestroyInstance();
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
