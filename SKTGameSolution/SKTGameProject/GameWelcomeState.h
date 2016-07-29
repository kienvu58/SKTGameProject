#pragma once
#include <Common/FSM/State.h>
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
private:
};

