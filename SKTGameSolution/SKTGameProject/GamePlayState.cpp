#include "GamePlayState.h"
#include "../GraphicsEngine/ResourceManager.h"
#include "../GraphicsEngine/AnimationManager.h"
#include "../GraphicsEngine/FrameManager.h"
#include "../GraphicsEngine/TextManager.h"

static Sprite spriteGoku;

GamePlayState::GamePlayState()
{
}

void GamePlayState::Enter(Game* game)
{

}

void GamePlayState::Execute(Game* game)
{
}

void GamePlayState::Exit(Game* game)
{
}

void GamePlayState::Render(Game* game)
{
}

GamePlayState* GamePlayState::GetInstance()
{
	static GamePlayState instance;
	return &instance;
}

void GamePlayState::Clear()
{
}

void GamePlayState::Init(const char* filePath)
{
}

GamePlayState::~GamePlayState()
{
}
