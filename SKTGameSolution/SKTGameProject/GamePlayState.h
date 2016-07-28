#pragma once
#include <Common/FSM/State.h>
#include "EntityPlayer.h"
#include "Game.h"

class GamePlayState : public State<Game>
{
public:
	GamePlayState();
	~GamePlayState();
	void Enter(Game* game) override;
	void Execute(Game* game) override;
	void Exit(Game* game) override;
	void Render(Game* game) override;
	void Init(const char* filePath);

	static GamePlayState* GetInstance();
	void Clear();
private:

};

