#pragma once
#include "Entity.h"
#include <map>
#include "EntityMinion.h"

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

	void Init(const char* filePath) override;

	float GetChanceToSpawnMinion(float difficulty, int prototypeId) const;
	int GetNumSpawnMinion(float difficulty, int numOnTheScreen, int prototypeId);
	void SpawnMinions();
	void RealeaseMinions(EntityMinion* minion);
private:
	// first int is prototypeId
	std::map<int, float> m_mapChanceWeights;
	std::map<int, float> m_mapNumSpawnWeights;
	std::map<int, int> m_mapInitNum;
};

