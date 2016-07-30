#pragma once
#include <Box2D/Dynamics/b2Body.h>
#include "Entity.h"
#include "../GraphicsEngine/Frame.h"
#include "../GraphicsEngine/Sprite.h"

class KiBlast :
	public Entity
{
public:
	KiBlast();
	~KiBlast();

	void Update() override;
	void Render() override;
	Entity* Clone() override;
	EntityType GetType() override;
	bool HandleMessage(const Telegram& telegram) override;

	void InitBody(const b2BodyDef &bodyDef, const b2FixtureDef &fixtureDef);
	void Create(float startTime, b2Vec2 direction);

private:
	b2Body* m_pBody;

	// KiBlast has to be charged, before it can be fired
	float m_fStartTime;
	float m_fChargeTime;
	float m_fSpeed;

	Frame* m_frameCharging;
	Frame* m_frameFlying;

	Sprite m_Sprite;
};

