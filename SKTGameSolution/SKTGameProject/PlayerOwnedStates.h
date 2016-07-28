#pragma once
#include <Common/FSM/State.h>
#include "EntityPlayer.h"

class PlayerMovingState :
	public State<EntityPlayer>
{
public:
	~PlayerMovingState();

	void Enter(EntityPlayer* entity) override;
	void Execute(EntityPlayer* entity) override;
	void Exit(EntityPlayer* entity) override;
	void Render(EntityPlayer* entity) override;

	static PlayerMovingState* GetInstance();
private:
	PlayerMovingState();
};


class PlayerStandingState :
	public State<EntityPlayer>
{
public:
	~PlayerStandingState();

	void Enter(EntityPlayer* entity) override;
	void Execute(EntityPlayer* entity) override;
	void Exit(EntityPlayer* entity) override;
	void Render(EntityPlayer* entity) override;

	static PlayerStandingState* GetInstance();
private:
	PlayerStandingState();
};



