#include "GameOverState.h"
#include "SingletonClasses.h"

GameOverState::GameOverState()
{
}

void GameOverState::Enter(Game* game)
{
}

void GameOverState::Execute(Game* game)
{
	m_Background->Update();

}

void GameOverState::Exit(Game* game)
{
}

void GameOverState::Render(Game* game)
{
	m_Background->Render();
}

void GameOverState::Init(const char* filePath)
{
	m_Background = new EntityStatic();
	m_Background->InitSprite(2, 102, 1);
}

bool GameOverState::OnMessage(Game*, const Telegram&)
{
	return false;
}

GameOverState::~GameOverState()
{
	delete m_Background;
}
