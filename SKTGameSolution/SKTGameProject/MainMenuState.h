#pragma once
#include <Common/FSM/State.h>
#include "Game.h"

class MainMenuState : public State<class Game>
{
public:
	~MainMenuState();

	void Enter(Game* game) override;
	void Execute(Game* game) override;
	void Exit(Game* game) override;
	void Render(Game* game) override;
	static MainMenuState* GetInstance();
private:
	MainMenuState();
};

