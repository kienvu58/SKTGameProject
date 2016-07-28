#pragma once
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
	void SetAnimations(std::vector<Animation*> animations);
	void SetFrameToSprite(Frame* frame);
	Animation* GetAnimation(int index);
	void ResetFramesInfo();
	void SetCurrentFrame(int currentFrame);
	float GetCurrentDelay() const;
	int GetCurrentFrame() const;
	void UpdateAnimationDelay();

	// must remove this method
	void SetSpriteData(int index, Vector2 position);

	//Physics functions
	void InitBody(b2BodyDef &bodyDef, b2FixtureDef &fixtureDef);
	b2Body* GetBody() const;

	//Material
	void Reset();

protected:
	//Owned Attribute
	float m_fCurrentHealth;
	float m_fMaxHealth;

	//Graphic info
	Sprite m_Sprite;

	//Animation info
	std::vector<Animation*> m_vecAnimations;
	int m_iCurrentFrame;
	int m_iLastFrame;
	float m_fCurrentDelay;

	//Physic info
	b2Body *m_pBody;
	float m_fMaxSpeed;
	float m_fMovementSpeed;
};

