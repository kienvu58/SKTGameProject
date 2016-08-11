#pragma once
#include "../GraphicsEngine/Animation.h"
#include "../GraphicsEngine/Sprite.h"
#include "Entity.h"
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>

const float MAX_OVERHEAT = 100.0f;
const float MIN_OVERHEAT = 0.0f;

class EntityLiving : public Entity
{
public:
	EntityLiving();
	EntityLiving(const EntityLiving& entityLiving);

	virtual ~EntityLiving();

	void Render() override = 0;
	void Update() override;
	EntityType GetType() override;
	bool HandleMessage(const Telegram& telegram) override = 0;

	//Init graphic info
	void InitSprite(int modelId, int frameId, int shaderId);
	void SetSprite(Sprite sprite);
	void ReverseSprite(bool isReversed);

	//Animation functions
	void SetAnimations(std::vector<Animation*> animations);
	Animation* GetAnimation(int index);
	void UpdateAnimationToSprite(Animation* animation);
	int GetFrameCount() const;
	void ResetCurrentAnimationInfo();
	bool IsFrameChanged() const;

	//Physics functions
	void InitBody(const b2BodyDef& bodyDef, const b2FixtureDef& fixtureDef, b2Vec2 velocity = b2Vec2_zero);
	b2Body* GetBody() const;
	float GetMaxSpeed() const;
	void ScaleVelocity(int scale) const;

	float GetMaxHealth() const;
	float GetMovementSpeed() const;
	void IncreaseOverheat(float amount);
	float GetCurrentOverheat() const;
	void DecreaseOverheatPerSecond(float amount);
	bool IsOverheated() const;

	//Material
	virtual void Reset() override;
	bool IsOutOfWall() const;

	//Battle functions
	float GetAttackDamage() const;
	void TakeDamage(float amount);
	bool IsDead() const;
	float GetCurrentHealth() const;

	//Clone
	Entity* Clone() override = 0;

	void Activate();

protected:
	//Owned Attribute
	float m_fCurrentHealth;
	float m_fMaxHealth;
	float m_fCurrentOverHeat;
	bool m_bIsOverheated;
	float m_fAttackDamage;

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
	b2PolygonShape m_b2PolygonShape;
	b2BodyDef m_b2BodyDef;
	b2FixtureDef m_b2FixtureDef;
};

