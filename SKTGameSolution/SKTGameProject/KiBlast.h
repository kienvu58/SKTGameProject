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

	void InitSprite(int modelId, int frameId, int shaderId);
	void InitBody(const b2BodyDef &bodyDef, const b2FixtureDef &fixtureDef);
	void Fire(b2Vec2 position, int direction);

private:
	b2Body* m_pBody;
	float m_fSpeed;
	Sprite m_Sprite;
	
	// direction of ki blast, 1: left to right, -1: right to left
	int m_iDirection;
};

