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
	EntityType GetType() override;
	bool HandleMessage(const Telegram& telegram) override;

	//Init graphic info
	void InitSprite(int modelId, int spriteSheetId, int shadersId);
	void SetSprite(Sprite sprite);
	void ReverseSprite(bool isReversed);

	//Animation functions
	void SetAnimations(std::vector<Animation*> animations);
	Animation* GetAnimation(int index);
	void UpdateAnimationToSprite(Animation* animation);
	int GetFrameCount() const;
	void ResetCurrentAnimationInfo();

	// must remove this method
	void SetSpriteData(int index, Vector2 position);

	//Physics functions
	void InitBody(const b2BodyDef& bodyDef, const b2FixtureDef& fixtureDef, b2Vec2 velocity = b2Vec2_zero);
	b2Body* GetBody() const;
	float GetMaxSpeed() const;
	void SetBody(b2Body* body);

	float GetMovementSpeed() const;

	//Material
	void Reset();

	//clone
	Entity* Clone() override = 0;

protected:
	//Owned Attribute
	float m_fCurrentHealth;
	float m_fMaxHealth;

	//Graphic info
	Sprite m_Sprite;
	bool m_bIsReversed;

	//Animation info
	std::vector<Animation*> m_vecAnimations;
	int m_iCurrentFrameIndex;
	int m_iLastFrameIndex;
	float m_fCurrentDelay;
	int m_iFrameCount;

	//Physic info
	b2Body *m_pBody;
	float m_fMaxSpeed;
	float m_fMovementSpeed;
};

