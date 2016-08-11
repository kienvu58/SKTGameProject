#pragma once
#include <Box2D/Dynamics/b2Body.h>
#include "../GraphicsEngine/Sprite.h"
#include "EntityBullet.h"
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>

class EntityKiBlast :
	public EntityBullet
{
public:
	EntityKiBlast();
	EntityKiBlast(const EntityKiBlast& other);
	~EntityKiBlast();

	void Update() override;
	void Render() override;
	Entity* Clone() override;
	EntityType GetType() override;
	bool HandleMessage(const Telegram& telegram) override;

	void InitSprite(int modelId, int frameId, int shaderId);
	void InitBody(const b2BodyDef& bodyDef, const b2FixtureDef& fixtureDef);
	void Trigger() const;
	void Fire(b2Vec2 position, int direction) override;
	void Reset() override;
	void Explode();

	void Init(int prototypeId, const char* dataPath) override;

	void SetSprite(Sprite sprite);
	void SetSpeed(float speed);

	bool IsOutOfWall() const;
	b2Body* GetBody() const;

private:
	b2Body* m_pBody;
	Sprite m_Sprite;

	int m_iExplosionPID;
	int m_iTriggerEffectPID;

	b2PolygonShape m_b2PolygonShape;
	b2BodyDef m_b2BodyDef;
	b2FixtureDef m_b2FixtureDef;
};
