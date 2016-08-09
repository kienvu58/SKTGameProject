#pragma once
#include <Common/FSM/State.h>
#include "EntityPlayer.h"
#include "Game.h"
#include "Pool.h"
#include "EntityStatic.h"
#include "Spawner.h"

class GamePlayState : public State<Game>
{
public:
	GamePlayState();
	~GamePlayState();
	void Enter(Game* game) override;
	static void PressButton(Game* game);
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
	EntityStatic* m_Background;
	EntityStatic* m_Button_Pause;

	EntityPlayer* m_Player;
	
	// map to store minion by protypeId
	std::map<int, std::vector<Entity*>*> m_mapCurrentEntities;

	//spawner
	Spawner m_spawner;
};
