#include "Game.h"
#include "GamePlayState.h"
#include "MainMenuState.h"
#include "GameWelcomeState.h"
#include "GameOptionState.h"
#include "SingletonClasses.h"

Game::Game(): m_pStateMachine(new StateMachine<Game>(this)),
              m_fPlayingTime(0), m_fDifficulty(0)
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
	GS_Pause::GetInstance()->Init("");
	GS_GameOver::GetInstance()->Init("");
}

void Game::CreateStateInstances()
{
	GS_Welcome::CreateInstance();
	GS_MainMenu::CreateInstance();
	GS_GamePlay::CreateInstance();
	GS_Option::CreateInstance();
	GS_Pause::CreateInstance();
	GS_GameOver::CreateInstance();

	PS_Global::CreateInstance();
	PS_Firing::CreateInstance();
	PS_Moving::CreateInstance();
	PS_Standing::CreateInstance();
	PS_FiringSpecial::CreateInstance();
	PS_FiringUltimate::CreateInstance();
	PS_TakingDamage::CreateInstance();
	PS_FallToDead::CreateInstance();
	PS_Charging::CreateInstance();

	MS_Wandering::CreateInstance();
	MS_Global::CreateInstance();

	CJS_Global::CreateInstance();
	CJS_Wandering::CreateInstance();
	CJS_Attacking::CreateInstance();
	
	CS_Global::CreateInstance();
	CS_Wandering::CreateInstance();
	CS_Attacking::CreateInstance();
	CS_Dodging::CreateInstance();
}

void Game::DestroyStateInstances()
{
	GS_Welcome::DestroyInstance();
	GS_MainMenu::DestroyInstance();
	GS_GamePlay::DestroyInstance();
	GS_Option::DestroyInstance();
	GS_Pause::DestroyInstance();
	GS_GameOver::DestroyInstance();

	PS_Global::DestroyInstance();
	PS_Firing::DestroyInstance();
	PS_Moving::DestroyInstance();
	PS_Standing::DestroyInstance();
	PS_FiringSpecial::DestroyInstance();
	PS_FiringUltimate::DestroyInstance();
	PS_TakingDamage::DestroyInstance();
	PS_FallToDead::DestroyInstance();
	PS_Charging::DestroyInstance();

	MS_Wandering::DestroyInstance();
	MS_Global::DestroyInstance();

	CJS_Global::DestroyInstance();
	CJS_Wandering::DestroyInstance();
	CJS_Attacking::DestroyInstance();

	CS_Global::DestroyInstance();
	CS_Wandering::DestroyInstance();
	CS_Attacking::DestroyInstance();
	CS_Dodging::DestroyInstance();
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

bool Game::HandleMessage(const Telegram& telegram)
{
	return m_pStateMachine->HandleMessage(telegram);
}

EntityType Game::GetType()
{
	return GAME;
}

Entity* Game::Clone()
{
	return nullptr;
}

void Game::IncreasePlayingTime(float amount)
{
	m_fPlayingTime += amount;
}

float Game::GetPlayingTime() const
{
	return m_fPlayingTime;
}

void Game::UpdateDifficulty(int currentScore)
{
	float playingTimeWeight = 1;
	float currentScoreWeight = 1.0f/50;

	m_fDifficulty = playingTimeWeight * MinutesFromSeconds(m_fPlayingTime) + currentScoreWeight * currentScore + 1; 
}

float Game::GetDifficulty() const
{
	return m_fDifficulty;
}

void Game::Reset()
{
	m_fPlayingTime = 0;
	GS_GamePlay::GetInstance()->Reset();
}
