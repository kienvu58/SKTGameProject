#pragma once
#include "Entity.h"
#include <Box2D/Dynamics/b2Body.h>
#include "EntityEffect.h"
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>

class EntityBarrier :
	public Entity
{
public:
	EntityBarrier();
	EntityBarrier(const EntityBarrier& other);
	~EntityBarrier();

	void Render() override;
	void Update() override;
	bool HandleMessage(const Telegram& telegram) override;
	Entity* Clone() override;

	EntityType GetType() override;
	void Init(int prototypeId, const char* dataPath) override;
	void InitBody(const b2BodyDef& bodyDef, const b2FixtureDef& fixtureDef);
	void Reset() override;

	void Activate(b2Vec2 position);
	void Stop();

private:
	b2Body* m_pBody;
	EntityEffect* m_pBarrierEffect;
	int m_iBarrierEffectPID;

	b2CircleShape m_b2CircleShape;
	b2BodyDef m_b2BodyDef;
	b2FixtureDef m_b2FixtureDef;
};

