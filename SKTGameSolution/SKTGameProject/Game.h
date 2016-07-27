#pragma once
#include <Common/FSM/StateMachine.h>

class Game
{
public:
	~Game();

	void Init();
	void Update();
	void Render();
	static Game* GetInstance();
	static void DestroyInstance();
private:
	Game();
	StateMachine<Game>* m_pStateMachine;
	static Game* s_Instance;
};

