#include <json.hpp>
#include <fstream>
#include "FactoryEntity.h"
#include "../GraphicsEngine/HelperFunctions.h"
#include "SingletonClasses.h"
#include "Definations.h"
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include "EntityKiBlast.h"

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
		if (entityType.compare("ENTITY_KIBLAST") == 0)
			entity = new EntityKiBlast();

		if (entity)
		{
			entity->Init(id, dataPath.c_str());
			m_mapPrototypes.insert(std::pair<int, Entity*>(id, entity));
		}
	}
}

Entity* FactoryEntity::GetPrototypeById(int prototypeId) const
{
	return GetResourceById<int, Entity>(prototypeId, m_mapPrototypes);
}
