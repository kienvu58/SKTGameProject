#pragma once
#include <Common/FSM/State.h>
#include "EntityPlayer.h"

class PlayerGlobalState :
	public State<EntityPlayer>
{
public:
	~PlayerGlobalState();

	void Enter(EntityPlayer* entity) override;
	void Execute(EntityPlayer* entity) override;
	void Exit(EntityPlayer* entity) override;
	void Render(EntityPlayer* entity) override;

	static PlayerGlobalState* GetInstance();
private:
	PlayerGlobalState();
};


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


class PlayerFiringState :
	public State<EntityPlayer>
{
public:
	~PlayerFiringState();

	void Enter(EntityPlayer* entity) override;
	void Execute(EntityPlayer* entity) override;
	void Exit(EntityPlayer* entity) override;
	void Render(EntityPlayer* entity) override;

	static PlayerFiringState* GetInstance();
private:
	PlayerFiringState();
};

