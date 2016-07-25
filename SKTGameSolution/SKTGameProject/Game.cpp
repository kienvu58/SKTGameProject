#include "Game.h"
#include "GamePlayState.h"


Game::Game(): m_pStateMachine(new StateMachine<Game>(this)) 
{
	m_pStateMachine->SetGlobalState(nullptr);
	m_pStateMachine->SetCurrentState(GamePlayState::GetInstance());
	m_pStateMachine->ChangeState(GamePlayState::GetInstance());
}


Game::~Game()
{
	delete m_pStateMachine;
}

void Game::Update()
{
	m_pStateMachine->Update();
}

void Game::Render()
{
	m_pStateMachine->Render();
}

Game* Game::GetInstance()
{
	static Game instance;
	return &instance;
}
