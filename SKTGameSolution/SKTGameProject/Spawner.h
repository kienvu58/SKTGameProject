#pragma once
#include "Entity.h"
#include <map>
#include "EntityMinion.h"
#include "Pool.h"

class Spawner : public Entity
{
public:
	Spawner();
	~Spawner();

	void Render() override;
	void Update() override;
	bool HandleMessage(const Telegram& telegram) override;
	EntityType GetType() override;
	Entity* Clone() override;

	void Init(const char* filePath);
	float GetChanceToSpawnMinion(float difficulty, EntityType minionType) const;
	int GetNumSpawnMinion(float difficulty, int numOnTheScreen, EntityType minionType);
	void SpawnMinions();
	void ReaseMinions(EntityMinion* minion);
private:
	std::map<EntityType, float> m_mapChanceWeights;
	std::map<EntityType, float> m_mapNumSpawnWeights;
	std::map<EntityType, int> m_mapInitNum;

	Pool<EntityMinion>* m_pMinionPool;
};

