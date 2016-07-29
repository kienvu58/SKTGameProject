#pragma once
#include <Common/FSM/State.h>
#include "EntityPlayer.h"
#include "Game.h"

class MainMenuState : public State<Game>
{
public:
	MainMenuState();
	~MainMenuState();

	void Enter(Game* game) override;
	void Execute(Game* game) override;
	void Exit(Game* game) override;
	void Render(Game* game) override;
	void Init(const char* filePath);

private:
};
