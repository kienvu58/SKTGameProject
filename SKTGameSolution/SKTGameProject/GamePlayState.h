#pragma once
#include <Common/FSM/State.h>
#include "EntityPlayer.h"
#include "Game.h"
#include "EntityMinion.h"
#include "Pool.h"

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

private:
	EntityPlayer* m_Goku;
	EntityMinion* m_pTestMinion;
	Entity* m_pCloneMinion;

	//pools
	Pool<EntityMinion>* m_pMinionPool;

	//current entity on the screen
	std::vector<EntityMinion*> m_vCurrentEntities;
};
