#include "FactoryEntity.h"
#include "../GraphicsEngine/HelperFunctions.h"
#include <Box2D/Dynamics/b2Body.h>
#include "../Utilities/Math.h"
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include "EntityCellJunior.h"
#include "SingletonClasses.h"

FactoryEntity::FactoryEntity()
{
}


FactoryEntity::~FactoryEntity()
{
	ClearMap<EntityType, Entity>(*m_pPrototypes);
	delete m_pPrototypes;
	m_pPrototypes = nullptr;
}

void FactoryEntity::Init(char* filePath)
{
	m_pPrototypes = new std::map<EntityType, Entity*>();

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(0, 0);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(MetersFromPixels(128) / 2 / 2, MetersFromPixels(128) / 2 / 2);

	b2FixtureDef fixture;
	fixture.shape = &boxShape;
	fixture.restitution = 0.0f;
	fixture.filter.groupIndex = -1;

	//CellJunior prototype
	EntityCellJunior* cellJuniorPrototype = new EntityCellJunior();
	cellJuniorPrototype->InitSprite(1, 28, 1);
	cellJuniorPrototype->ReverseSprite(true);
	cellJuniorPrototype->InitBody(bodyDef, fixture, b2Vec2(-2, 0));
	m_pPrototypes->insert(std::pair<EntityType, Entity*>(ENTITY_CELLJUNIOR, cellJuniorPrototype));

	//Goku (Player) prototype
	EntityPlayer* gokuPrototype = new EntityPlayer();
	gokuPrototype->InitSprite(1, 1, 1);
	std::vector<Animation*> gokuAnimations;
	gokuAnimations.push_back(AnimationMgr->GetAnimationById(1));
	gokuAnimations.push_back(AnimationMgr->GetAnimationById(2));
	gokuAnimations.push_back(AnimationMgr->GetAnimationById(3));
	gokuAnimations.push_back(AnimationMgr->GetAnimationById(4));
	gokuAnimations.push_back(AnimationMgr->GetAnimationById(5));
	gokuAnimations.push_back(AnimationMgr->GetAnimationById(6));
	gokuAnimations.push_back(AnimationMgr->GetAnimationById(7));
	gokuAnimations.push_back(AnimationMgr->GetAnimationById(8));
	gokuAnimations.push_back(AnimationMgr->GetAnimationById(9));
	gokuPrototype->SetAnimations(gokuAnimations);
	bodyDef.position = b2Vec2(-5,0);
	gokuPrototype->InitBody(bodyDef, fixture);
	m_pPrototypes->insert(std::pair<EntityType, Entity*>(ENTITY_PLAYER, gokuPrototype));
}

Entity* FactoryEntity::GetPrototype(EntityType type)
{
	return GetResourceById<EntityType, Entity>(type, *m_pPrototypes);
}
