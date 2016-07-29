#pragma once
#include <Common/FSM/State.h>
#include "Game.h"
#include "EntityStatic.h"
#include "../GraphicsEngine/InputManager.h"


class GameOptionState : public State<Game>
{
public:
	GameOptionState();
	~GameOptionState();

	void Enter(Game* game) override;
	void Execute(Game* game) override;
	void Exit(Game* game) override;
	void Render(Game* game) override;
	void Init(const char* filePath);

	static GameOptionState* GetInstance();
	void Clear();
private:
	EntityStatic *m_Background;
};

