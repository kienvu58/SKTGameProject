#pragma once
#include <Common/FSM/State.h>
#include "EntityPlayer.h"
#include "Game.h"
#include "Pool.h"
#include "EntityKiBlast.h"
#include "EntityBeamWave.h"
#include "EntityStatic.h"
#include "Spawner.h"

class GamePlayState : public State<Game>
{
public:
	GamePlayState();
	~GamePlayState();
	void Enter(Game* game) override;
	void Execute(Game* game) override;
	void Exit(Game* game) override;
	void Render(Game* game) override;
	void Init(const char* filePath);

	bool OnMessage(Game*, const Telegram&) override;

	void AddEntitesToTheScreen(Entity* entity);
	void RemoveEntitiesOnTheScreen(Entity* entity);
	int GetNumEntitiesByType(EntityType type);
	int GetNumAllEntities();
	std::vector<Entity*>* GetEntitiesByType(EntityType type);
	EntityPlayer* GetPlayer() const;
private:
	EntityStatic *m_Background;
	EntityPlayer* m_Goku;

	EntityStatic *m_Button_Pause;

	//current entity on the screen
	std::vector<EntityKiBlast*> m_vCurrentKiBlasts;
	std::vector<EntityBeamWave*> m_vCurrentBeamWaves;

	std::map<EntityType, std::vector<Entity*>*> m_mapCurrentEntities;

	//spawner
	Spawner m_spawner;
};
