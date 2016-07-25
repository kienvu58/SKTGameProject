#pragma once
#include <Common/FSM/State.h>
#include "EntityPlayer.h"

class PlayerMovingState : State<EntityPlayer>
{
public:
	PlayerMovingState();
	~PlayerMovingState();
};

