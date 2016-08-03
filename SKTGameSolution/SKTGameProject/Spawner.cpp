#include "Spawner.h"
#include "../Utilities/Math.h"
#include "SingletonClasses.h"

Spawner::Spawner()
{
}

Spawner::~Spawner()
{
	delete m_pMinionPool;
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

	//tmp hard code.
	m_mapChanceWeights.insert(std::pair<EntityType, float>(ENTITY_CELLJUNIOR, 1));
	m_mapNumSpawnWeights.insert(std::pair<EntityType, float>(ENTITY_CELLJUNIOR, 2.0f / 5));
	m_mapInitNum.insert(std::pair<EntityType, int>(ENTITY_CELLJUNIOR, 10));

	m_pMinionPool = new Pool<EntityMinion>();

	int nMaxMinions = 100;
	for (int i = 0; i<nMaxMinions; i++)
	{
		EntityMinion* minion = dynamic_cast<EntityCellJunior*>(Factory->GetPrototype(ENTITY_CELLJUNIOR)->Clone());
		minion->GetBody()->SetTransform(b2Vec2(rand() % 10, (rand() - rand()) % 6), 0);
		m_pMinionPool->Add(minion);
	}
}

float Spawner::GetChanceToSpawnMinion(float difficulty, EntityType minionType) const
{
	auto it = m_mapChanceWeights.find(minionType);
	float chance = 1;
	if (it != m_mapChanceWeights.end())
	{
		chance = Sigmoid(difficulty, it->second);
	}
	return chance;
}

int Spawner::GetNumSpawnMinion(float difficulty, int numOnTheScreen, EntityType minionType)
{
	int numSpawn = 0;
	auto it = m_mapNumSpawnWeights.find(minionType);
	auto it2 = m_mapInitNum.find(minionType);
	if (it != m_mapNumSpawnWeights.end() && it2 != m_mapInitNum.end())
	{
		numSpawn = it->second * difficulty - numOnTheScreen + it2->second;
	}
	return numSpawn;
}

void Spawner::SpawnMinions()
{
	for (auto it : m_mapChanceWeights)
	{
		EntityType type = it.first;
		int numOnTheScreen = GS_GamePlay::GetInstance()->GetNumEntitiesByType(type);
		float difficulty = GameInstance->GetDifficulty();
		int numToSpawn = GetNumSpawnMinion(difficulty, numOnTheScreen, type);
		
		for (int i=0; i<numToSpawn; i++)
		{
			if (rand() * 1.0f / RAND_MAX <= GetChanceToSpawnMinion(difficulty, type))
			{
				EntityMinion* entity;
				entity = m_pMinionPool->GetEntity();
				entity->GetBody()->SetActive(true);
				entity->GetBody()->SetTransform(b2Vec2(10, (rand() - rand()) % 6), 0);
				entity->GetBody()->SetLinearVelocity(b2Vec2(-4, 0));
				GS_GamePlay::GetInstance()->AddEntitesToTheScreen(type, entity);
			}	
		}
	}
}

void Spawner::ReaseMinions(EntityMinion* minion)
{
	if (m_pMinionPool)
	{
		m_pMinionPool->ReleaseEntity(minion);
	}
}
