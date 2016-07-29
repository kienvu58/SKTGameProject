#pragma once
#include <Common/FSM/State.h>
#include "EntityPlayer.h"
#include "Game.h"
#include "EntityMinion.h"
#include "Pool.h"

class GamePlayState : public State<Game>
{
public:
	~GamePlayState();
	void Enter(Game* game) override;
	void Execute(Game* game) override;
	void Exit(Game* game) override;
	void Render(Game* game) override;
	void Init(const char* filePath);

	static GamePlayState* GetInstance();
	void Clear();
private:
	GamePlayState();
	EntityPlayer* m_Goku;
	EntityMinion* m_pTestMinion;

	//pools
	Pool<EntityMinion>* m_pMinionPool;

	//current entity on the screen
	std::vector<EntityMinion*> m_vCurrentEntities;
};
