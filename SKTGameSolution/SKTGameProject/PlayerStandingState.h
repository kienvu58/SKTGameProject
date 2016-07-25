#pragma once
#include "EntityPlayer.h"
#include <Common/FSM/State.h>

class PlayerStandingState :
	public State<EntityPlayer>
{
public:
	PlayerStandingState();

	void Enter(EntityPlayer* entity) override;
	void Execute(EntityPlayer* entity) override;
	void Exit(EntityPlayer* entity) override;
	void Render(EntityPlayer* entity) override;

	static PlayerStandingState* GetInstance();
private:
	~PlayerStandingState();
};

