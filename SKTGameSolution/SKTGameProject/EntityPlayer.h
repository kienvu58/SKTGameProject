#pragma once
#include <Common/FSM/StateMachine.h>
#include "Entity.h"
#include "../GraphicsEngine/Sprite.h"

#define ANIMATION_TIME 1.0f

class EntityPlayer :
	public Entity
{
public:
	EntityPlayer();
	~EntityPlayer();

	void Render() override;
	void Update() override;
	Sprite* m_pSprite;
private:
	StateMachine<EntityPlayer>* m_pStateMachine;
};
