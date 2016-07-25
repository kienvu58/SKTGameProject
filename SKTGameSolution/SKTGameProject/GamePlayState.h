#pragma once
#include <Common/FSM/State.h>
#include "EntityPlayer.h"

class GamePlayState : public State<class Game>
{
public:
	GamePlayState();

	void Enter(Game* game) override;
	void Execute(Game* game) override;
	void Exit(Game* game) override;
	void Render(Game* game) override;

	static GamePlayState* GetInstance();
private:
	~GamePlayState();
	EntityPlayer m_Goku;
};

