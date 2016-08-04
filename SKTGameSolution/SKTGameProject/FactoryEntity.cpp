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
	boxShape.SetAsBox(MetersFromPixels(128) / 2 / 4, MetersFromPixels(128) / 2 / 4);

	b2FixtureDef fixture;
	fixture.shape = &boxShape;
	fixture.restitution = 0.5f;
	fixture.density = 10;
//	fixture.filter.groupIndex = -1;
	fixture.filter.categoryBits = CATEGORY_MINION;
	fixture.filter.maskBits = CATEGORY_PLAYER | CATEGORY_KI_BLAST;

	//CellJunior prototype
	EntityCellJunior* cellJuniorPrototype = new EntityCellJunior();
	cellJuniorPrototype->InitSprite(1, 28, 1);
	cellJuniorPrototype->ReverseSprite(true);
	cellJuniorPrototype->InitBody(bodyDef, fixture, b2Vec2(-2, 0));
	cellJuniorPrototype->GetBody()->SetActive(false);
	m_pPrototypes->insert(std::pair<EntityType, Entity*>(ENTITY_CELLJUNIOR, cellJuniorPrototype));

	//Goku (Player) prototype
//	fixture.filter.groupIndex = 1;
	boxShape.SetAsBox(MetersFromPixels(128) / 2 / 2, MetersFromPixels(128) / 2 / 2);
	fixture.filter.categoryBits = CATEGORY_PLAYER;
	fixture.filter.maskBits = CATEGORY_WALL | CATEGORY_MINION;
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
	bodyDef.position = b2Vec2(0, 0);
	gokuPrototype->InitBody(bodyDef, fixture);
	m_pPrototypes->insert(std::pair<EntityType, Entity*>(ENTITY_PLAYER, gokuPrototype));

	//Kiblast prototype
	KiBlast* kiBlastPrototype = new KiBlast();
	boxShape.SetAsBox(MetersFromPixels(24), MetersFromPixels(12));
	fixture.isSensor = true;
	fixture.filter.categoryBits = CATEGORY_KI_BLAST;
	fixture.filter.maskBits = CATEGORY_MINION;
	kiBlastPrototype->InitBody(bodyDef, fixture);
	kiBlastPrototype->InitSprite(4, 36, 1);
	kiBlastPrototype->GetBody()->SetActive(false);
	m_pPrototypes->insert(std::pair<EntityType, Entity*>(KI_BLAST, kiBlastPrototype));
}

Entity* FactoryEntity::GetPrototype(EntityType type)
{
	return GetResourceById<EntityType, Entity>(type, *m_pPrototypes);
}
