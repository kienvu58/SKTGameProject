#pragma once
#include <Common/FSM/StateMachine.h>
#include "Entity.h"
#include "../GraphicsEngine/Sprite.h"
#include "../GraphicsEngine/Animation.h"
#include <Box2D/Dynamics/b2Body.h>
#include <map>

class EntityPlayer :
	public Entity
{
public:
	EntityPlayer();
	~EntityPlayer();

	void Render() override;
	void Update() override;

	void InitSprite(int modelId, int spriteSheetId, int shadersId);
	void InitAnimations(std::map<std::string, Animation*> mapAnimations);
	void SetFrameToSprite(Frame* frame);
	Animation* GetAnimationByName(std::string name);
	StateMachine<EntityPlayer>* GetFSM() const;

	int currentFrame;
	int delay;
private:
	StateMachine<EntityPlayer>* m_pStateMachine;
	Sprite m_Sprite;
	std::map<std::string, Animation*> m_mapAnimations;
};
