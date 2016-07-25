#pragma once
#include <Common/FSM/StateMachine.h>

class Game
{
public:
	~Game();

	void Update();
	void Render();
	static Game* GetInstance();

private:
	Game();
	StateMachine<Game>* m_pStateMachine;
};

