#pragma once
#include <Common/FSM/StateMachine.h>

class Game
{
public:
	Game();
	~Game();

	void Init();
	void CreateStateInstances();
	void DestroyStateInstances();
	void Update();
	void Render();

	StateMachine<Game>* GetFSM() const;
private:
	StateMachine<Game>* m_pStateMachine;
};

