#pragma once
#include <Common/FSM/StateMachine.h>
#include "Entity.h"
#include "../GraphicsEngine/Sprite.h"
#include "../GraphicsEngine/Animation.h"

#define ANIMATION_TIME 1.0f

class EntityPlayer :
	public Entity
{
public:
	EntityPlayer();
	~EntityPlayer();

	void Render() override;
	void Update() override;

	void InitSprite(int modelId, int spriteSheetId, int shadersId);
	static void InitAnimations(int animationStandingId, int animationMovingForwardId, int animationMovingBackwardId);
	void SetFrameToSprite(Frame* frame);
	StateMachine<EntityPlayer>* GetFSM() const;

	static Animation* s_AnimationStanding;
	static Animation* s_AnimationMovingForward;
	static Animation* s_AnimationMovingBackward;
private:
	StateMachine<EntityPlayer>* m_pStateMachine;
	Sprite m_Sprite;
};
