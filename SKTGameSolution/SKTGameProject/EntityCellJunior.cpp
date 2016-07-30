#include "EntityCellJunior.h"
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>


EntityCellJunior::EntityCellJunior()
{
	m_pSteeringBehavior->WanderOn();
}


EntityCellJunior::~EntityCellJunior()
{
}

Entity* EntityCellJunior::Clone()
{
	EntityMinion* cloneMinion = new EntityCellJunior();
	//graphic
	cloneMinion->SetSprite(this->m_Sprite);
	cloneMinion->SetAnimations(this->m_vecAnimations);
	cloneMinion->ReverseSprite(this->m_bIsReversed);

	//physics
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(5, 0);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(MetersFromPixels(128) / 2 / 2, MetersFromPixels(128) / 2 / 2);

	b2FixtureDef fixture;
	fixture.shape = &boxShape;
	fixture.restitution = 1.0f;
	cloneMinion->InitBody(bodyDef, fixture, b2Vec2(-2, 0));

	return cloneMinion;
}
