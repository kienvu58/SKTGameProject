#pragma once
#include "Entity.h"
#include <map>

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

private:
	std::map<EntityType, float> m_mapChanceWeights;
	std::map<EntityType, float> m_mapNumSpawnWeights;
};

