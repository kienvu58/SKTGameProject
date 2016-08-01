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

	bool OnMessage(EntityPlayer*, const Telegram&) override;
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


	bool OnMessage(EntityPlayer*, const Telegram&) override;
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

	bool OnMessage(EntityPlayer*, const Telegram&) override;
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

	bool OnMessage(EntityPlayer*, const Telegram&) override;
};


class PlayerFiringSpecialState :
	public State<EntityPlayer>
{
public:
	PlayerFiringSpecialState();
	~PlayerFiringSpecialState();

	void Enter(EntityPlayer* entity) override;
	void Execute(EntityPlayer* entity) override;
	void Exit(EntityPlayer* entity) override;
	void Render(EntityPlayer* entity) override;

	bool OnMessage(EntityPlayer*, const Telegram&) override;
};


class PlayerFiringUltimateState :
	public State<EntityPlayer>
{
public:
	PlayerFiringUltimateState();
	~PlayerFiringUltimateState();

	void Enter(EntityPlayer* entity) override;
	void Execute(EntityPlayer* entity) override;
	void Exit(EntityPlayer* entity) override;
	void Render(EntityPlayer* entity) override;

	bool OnMessage(EntityPlayer*, const Telegram&) override;
};

