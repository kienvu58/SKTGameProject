#pragma once
#include <Common/FSM/State.h>
#include "Game.h"
#include "EntityStatic.h"
class GameOverState : public State<Game>
{
public:
	GameOverState();
	~GameOverState();
	void Enter(Game* game) override;
	void Execute(Game* game) override;
	void Exit(Game* game) override;
	void Render(Game* game) override;
	void Init(const char* filePath);


	bool OnMessage(Game*, const Telegram&) override;
private:
	EntityStatic *m_Background;
};
