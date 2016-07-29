#pragma once
#include <Common/FSM/State.h>
#include "EntityPlayer.h"

class PlayerGlobalState :
	public State<EntityPlayer>
{
public:
	PlayerGlobalState();
	~PlayerGlobalState();

	void Enter(EntityPlayer* entity) override;
	void Execute(EntityPlayer* entity) override;
	void Exit(EntityPlayer* entity) override;
	void Render(EntityPlayer* entity) override;
};


class PlayerMovingState :
	public State<EntityPlayer>
{
public:
	PlayerMovingState();
	~PlayerMovingState();

	void Enter(EntityPlayer* entity) override;
	void Execute(EntityPlayer* entity) override;
	void Exit(EntityPlayer* entity) override;
	void Render(EntityPlayer* entity) override;

};


class PlayerStandingState :
	public State<EntityPlayer>
{
public:
	PlayerStandingState();
	~PlayerStandingState();

	void Enter(EntityPlayer* entity) override;
	void Execute(EntityPlayer* entity) override;
	void Exit(EntityPlayer* entity) override;
	void Render(EntityPlayer* entity) override;

};


class PlayerFiringState :
	public State<EntityPlayer>
{
public:
	PlayerFiringState();
	~PlayerFiringState();

	void Enter(EntityPlayer* entity) override;
	void Execute(EntityPlayer* entity) override;
	void Exit(EntityPlayer* entity) override;
	void Render(EntityPlayer* entity) override;

};

