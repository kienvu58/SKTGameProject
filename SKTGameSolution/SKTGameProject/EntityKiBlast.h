#pragma once
#include <Box2D/Dynamics/b2Body.h>
#include "../GraphicsEngine/Sprite.h"
#include "EntityBullet.h"

class EntityKiBlast :
	public EntityBullet
{
public:
	EntityKiBlast();
	~EntityKiBlast();

	void Update() override;
	void Render() override;
	Entity* Clone() override;
	EntityType GetType() override;
	bool HandleMessage(const Telegram& telegram) override;

	void InitSprite(int modelId, int frameId, int shaderId);
	void InitBody(const b2BodyDef& bodyDef, const b2FixtureDef& fixtureDef);
	void Fire(b2Vec2 position, int direction = 1);

	void SetSprite(Sprite sprite);
	void SetSpeed(float speed);

	bool IsOutOfWall();
	b2Body* GetBody() const;

	//Batle functions
	float Attack() const;
private:
	b2Body* m_pBody;
	float m_fSpeed;
	Sprite m_Sprite;

	// direction of ki blast, 1: left to right, -1: right to left
	int m_iDirection;

	float m_fAttackDamage;
};
