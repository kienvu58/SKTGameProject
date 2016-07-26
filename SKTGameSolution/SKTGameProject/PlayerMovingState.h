#pragma once
#include "EntityPlayer.h"
#include <Common/FSM/State.h>

class PlayerMovingState :
	public State<EntityPlayer>
{
public:
	PlayerMovingState();

	void Enter(EntityPlayer* entity) override;
	void Execute(EntityPlayer* entity) override;
	void Exit(EntityPlayer* entity) override;
	void Render(EntityPlayer* entity) override;

	static PlayerMovingState* GetInstance();
private:
	~PlayerMovingState();
};

