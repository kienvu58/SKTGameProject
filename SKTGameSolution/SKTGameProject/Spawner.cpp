#include "Spawner.h"

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

	//tmp hard code.
	m_mapChanceWeights.insert(std::pair<EntityType, float>(ENTITY_CELLJUNIOR, 0.9));
	m_mapNumSpawnWeights.insert(std::pair<EntityType, float>(ENTITY_CELLJUNIOR, 10));
}

float Spawner::GetChanceToSpawnMinion(float difficulty, EntityType minionType) const
{
	auto it = m_mapChanceWeights.find(minionType);
	float chance = 1;
	if (it != m_mapChanceWeights.end())
	{
		chance = it->second * difficulty;
	}
	return chance;
}

int Spawner::GetNumSpawnMinion(float difficulty, int numOnTheScreen, EntityType minionType)
{
	int numSpawn = 0;
	auto it = m_mapNumSpawnWeights.find(minionType);
	if (it != m_mapNumSpawnWeights.end())
	{
		numSpawn = it->second * difficulty - numOnTheScreen;
	}
	return numSpawn;
}
