#pragma once
#include <Common/FSM/StateMachine.h>
#include "Entity.h"

class Game : public Entity
{
public:
	Game();
	~Game();

	void Init();
	void CreateStateInstances();
	void DestroyStateInstances();
	void Update() override;
	void Render() override;

	bool HandleMessage(const Telegram& telegram) override;
	EntityType GetType() override;
	Entity* Clone() override;

	StateMachine<Game>* GetFSM() const;
private:
	StateMachine<Game>* m_pStateMachine;
};

