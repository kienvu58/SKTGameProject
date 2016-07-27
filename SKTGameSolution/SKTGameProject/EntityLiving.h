#pragma once
#include <map>
#include "../GraphicsEngine/Animation.h"
#include "../GraphicsEngine/Sprite.h"
#include "Entity.h"

class EntityLiving : public Entity
{
public:
	EntityLiving();
	~EntityLiving();

	void Render() override = 0;
	void Update() override = 0;

	//Init graphic info
	void InitSprite(int modelId, int spriteSheetId, int shadersId);

	//Animation functions
	void InitAnimations(std::map<std::string, Animation*> mapAnimations);
	void SetFrameToSprite(Frame* frame);
	Animation* GetAnimationByName(std::string name);

	int currentFrame;
	int delay;

protected:
	//Graphic info
	Sprite m_Sprite;

	//Animation info
	std::map<std::string, Animation*> m_mapAnimations;

	//Physic info
};

