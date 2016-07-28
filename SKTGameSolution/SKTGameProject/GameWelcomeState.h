#pragma once
#include <Common/FSM/State.h>
#include "EntityPlayer.h"
#include "GamePlayState.h"
#include "../GraphicsEngine/ResourceManager.h"
#include <Windows.h>
#include "MainMenuState.h"
#include "Game.h"


class GameWelcomeState : public State<Game>
{
public:
	GameWelcomeState();
	~GameWelcomeState();

	void Enter(Game* game) override;
	void Execute(Game* game) override;
	void Exit(Game* game) override;
	void Render(Game* game) override;
	void Init(const char* filePath);

	static GameWelcomeState* GetInstance();
	void Clear();
private:
	
	EntityPlayer *m_Background;
};

