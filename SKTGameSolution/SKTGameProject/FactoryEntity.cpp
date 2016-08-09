#include <json.hpp>
#include <fstream>
#include "FactoryEntity.h"
#include "../GraphicsEngine/HelperFunctions.h"
#include "SingletonClasses.h"
#include "Definations.h"

FactoryEntity::FactoryEntity()
{
}


FactoryEntity::~FactoryEntity()
{
	ClearMap<int, Entity>(m_mapPrototypes);
}

void FactoryEntity::Init(const char* filePath)
{
	std::ifstream fin(filePath);
	nlohmann::json data(fin);
	fin.close();

	for (auto prototype : data["prototypes"])
	{
		auto id = prototype["id"].get<int>();
		auto entityType = prototype["entityType"].get<std::string>();
		auto dataPath = std::string(DATA_PATH);
		dataPath.append(prototype["dataPath"].get<std::string>());

		Entity* entity = nullptr;

		if (entityType.compare("ENTITY_PLAYER") == 0)
			entity = new EntityPlayer();
		if (entityType.compare("ENTITY_CELLJUNIOR") == 0)
			entity = new EntityCellJunior();
		if (entityType.compare("ENTITY_CELL") == 0)
			entity = new EntityCell();

		if (entity)
		{
			entity->Init(id, dataPath.c_str());
			m_mapPrototypes.insert(std::pair<int, Entity*>(id, entity));
		}
	}
	/*
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position = b2Vec2(0, 0);
	
		b2PolygonShape boxShape;
		boxShape.SetAsBox(MetersFromPixels(128) / 2 / 4, MetersFromPixels(128) / 2 / 4);
	
		b2FixtureDef fixture;
		fixture.shape = &boxShape;
		fixture.restitution = 0.5f;
		fixture.friction = 1;
	//	fixture.filter.groupIndex = -1;
		fixture.filter.categoryBits = CATEGORY_MINION;
		fixture.filter.maskBits = CATEGORY_PLAYER | CATEGORY_KI_BLAST;
	
		//CellJunior prototype
		EntityCellJunior* cellJuniorPrototype = new EntityCellJunior();
		cellJuniorPrototype->InitSprite(1, 28, 1);
		cellJuniorPrototype->ReverseSprite(true);
		cellJuniorPrototype->InitBody(bodyDef, fixture, b2Vec2(-2, 0));
		cellJuniorPrototype->GetBody()->SetActive(false);
		m_mapPrototypes.insert(std::pair<EntityType, Entity*>(ENTITY_CELLJUNIOR, cellJuniorPrototype));
	
		//Cell prototype
		EntityCell* cellPrototype = new EntityCell();
		cellPrototype->InitSprite(1, 1, 1);
		cellPrototype->ReverseSprite(true);
		cellPrototype->InitBody(bodyDef, fixture, b2Vec2(-1.5, 0));
		cellPrototype->GetBody()->SetActive(false);
		m_mapPrototypes.insert(std::pair<EntityType, Entity*>(ENTITY_CELL, cellPrototype));
	
		//Goku (Player) prototype
	//	fixture.filter.groupIndex = 1;
		fixture.restitution = 0;
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
		gokuAnimations.push_back(AnimationMgr->GetAnimationById(10));
		gokuAnimations.push_back(AnimationMgr->GetAnimationById(11));
		gokuPrototype->SetAnimations(gokuAnimations);
		bodyDef.position = b2Vec2(0, 0);
		gokuPrototype->InitBody(bodyDef, fixture);
		m_mapPrototypes.insert(std::pair<EntityType, Entity*>(ENTITY_PLAYER, gokuPrototype));
	
		//Kiblast prototype
		EntityKiBlast* kiBlastPrototype = new EntityKiBlast();
		boxShape.SetAsBox(MetersFromPixels(24), MetersFromPixels(12));
		fixture.isSensor = true;
		fixture.filter.categoryBits = CATEGORY_KI_BLAST;
		fixture.filter.maskBits = CATEGORY_MINION;
		kiBlastPrototype->InitBody(bodyDef, fixture);
		kiBlastPrototype->InitSprite(4, 66, 1);
		kiBlastPrototype->GetBody()->SetActive(false);
		m_mapPrototypes.insert(std::pair<EntityType, Entity*>(KI_BLAST, kiBlastPrototype));
	*/
}

Entity* FactoryEntity::GetPrototypeById(int prototypeId)
{
	return GetResourceById<int, Entity>(prototypeId, m_mapPrototypes);
}
