#include <json.hpp>
#include <fstream>
#include "Spawner.h"
#include "../Utilities/Math.h"
#include "SingletonClasses.h"
#include "Definations.h"

Spawner::Spawner()
{
}

Spawner::~Spawner()
{
}

void Spawner::Render()
{
}

void Spawner::Update()
{
}

bool Spawner::HandleMessage(const Telegram& telegram)
{
	return false;
}

EntityType Spawner::GetType()
{
	return SPAWNER;
}

Entity* Spawner::Clone()
{
	return nullptr;
}

void Spawner::Init(const char* filePath)
{
	//read file here.
	auto dataPath = std::string(DATA_PATH);
	dataPath.append(filePath);
	std::ifstream fin(dataPath);
	nlohmann::json data(fin);
	fin.close();

	for (auto info : data["data"])
	{
		int minionID = info["minionId"].get<int>();
		float chaneWeights = info["chanceWeights"].get<float>();
		float spawnWeights = info["spawnWeights"].get<float>();
		int initNumOnTheScreen = info["initNumOnTheScreen"].get<float>();
		m_mapChanceWeights.insert(std::pair<int, float>(minionID, chaneWeights));
		m_mapNumberToSpawnWeights.insert(std::pair<int, float>(minionID, spawnWeights));
		m_mapInitNum.insert(std::pair<int, int>(minionID, initNumOnTheScreen));
	}
//
//	//tmp hard code.
//	m_mapChanceWeights.insert(std::pair<int, float>(2, 1));
//	m_mapNumberToSpawnWeights.insert(std::pair<int, float>(2, 2.0f / 5));
//	m_mapInitNum.insert(std::pair<int, int>(2, 5));
//
//	m_mapChanceWeights.insert(std::pair<int, float>(69, 0.9));
//	m_mapNumberToSpawnWeights.insert(std::pair<int, float>(69, 2.0f / 5));
//	m_mapInitNum.insert(std::pair<int, int>(69, 1));
}

float Spawner::GetSpawnMinionChance(float difficulty, int prototypeId) const
{
	auto chanceWeight = m_mapChanceWeights.find(prototypeId);
	float chance = 1;
	if (chanceWeight != m_mapChanceWeights.end())
	{
		chance = Sigmoid(difficulty, chanceWeight->second);
	}
	return chance;
}

int Spawner::GetNumberOfMinionsToSpawn(float difficulty, int numOnTheScreen, int minionType)
{
	auto nMinionsToSpawn = 0;
	auto nMinionsToSpawnWeight = m_mapNumberToSpawnWeights.find(minionType);
	auto nInitMinions = m_mapInitNum.find(minionType);
	if (nMinionsToSpawnWeight != m_mapNumberToSpawnWeights.end() && nInitMinions != m_mapInitNum.end())
	{
		nMinionsToSpawn = nMinionsToSpawnWeight->second * difficulty - numOnTheScreen + nInitMinions->second;
	}
	return nMinionsToSpawn;
}

void Spawner::SpawnMinions()
{
	for (auto it : m_mapChanceWeights)
	{
		auto prototypeId = it.first;
		auto nMinionsOnScreen = GS_GamePlay::GetInstance()->GetNumberOfEntitiesByPrototypeId(prototypeId);
		auto difficulty = GameInstance->GetDifficulty();
		auto nMinionsToSpawn = GetNumberOfMinionsToSpawn(difficulty, nMinionsOnScreen, prototypeId);

		for (auto i = 0; i < nMinionsToSpawn; i++)
		{
			if (rand() * 1.0f / RAND_MAX <= GetSpawnMinionChance(difficulty, prototypeId))
			{
				auto entity = static_cast<EntityMinion*>(PoolMgr->GetEntityByPrototypeId(prototypeId));
				if (!entity)
				{
					return;
				}
				entity->Activate();
				entity->GetBody()->SetTransform(b2Vec2(10, (rand() - rand()) % 6), 0);
				entity->GetBody()->SetLinearVelocity(entity->GetMovementSpeed() * b2Vec2(-1, 0));
				GS_GamePlay::GetInstance()->AddEntityToTheScreen(entity);
			}
		}
	}
}

void Spawner::RealeaseMinions(EntityMinion* minion)
{
	if (minion)
	{
		PoolMgr->ReleaseEntity(minion);
	}
}
