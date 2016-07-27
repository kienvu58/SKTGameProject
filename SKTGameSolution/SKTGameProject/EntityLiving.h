#pragma once
#include <map>
#include "../GraphicsEngine/Animation.h"
#include "../GraphicsEngine/Sprite.h"
#include "Entity.h"
#include <Box2D/Dynamics/b2Body.h>

class EntityLiving : public Entity
{
public:
	EntityLiving();
	~EntityLiving();

	void Render() override = 0;
	void Update() override;

	//Init graphic info
	void InitSprite(int modelId, int spriteSheetId, int shadersId);

	//Animation functions
	void InitAnimations(std::map<std::string, Animation*> mapAnimations);
	void SetFrameToSprite(Frame* frame);
	Animation* GetAnimationByName(std::string name);

	// must remove this method
	void SetSpriteData(int index, Vector2 position);

	int currentFrame;
	int delay;

	//Physics functions
	void InitBody(b2BodyDef &bodyDef, b2FixtureDef &fixtureDef);

	//Material
	void Reset();

protected:
	//Owned Attribute
	float m_fCurrentHealth;
	float m_fMaxHealth;

	//Graphic info
	Sprite m_Sprite;

	//Animation info
	std::map<std::string, Animation*> m_mapAnimations;

	//Physic info
	b2Body *m_pBody;
	float m_fMaxSpeed;
	float m_fMovementSpeed;
};

