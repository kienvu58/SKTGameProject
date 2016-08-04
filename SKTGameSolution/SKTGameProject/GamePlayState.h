#pragma once
#include <Common/FSM/State.h>
#include "EntityPlayer.h"
#include "Game.h"
#include "EntityMinion.h"
#include "Pool.h"
#include "KiBlast.h"
#include "EntityCellJunior.h"
#include "FactoryEntity.h"
#include "BeamWave.h"
#include "EntityStatic.h"

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
private:
	EntityStatic *m_Background;
	EntityPlayer* m_Goku;
	EntityCellJunior* m_pTestMinion;
	Entity* m_pCloneMinion;
	EntityStatic *m_Button_Pause;

	//factory stores prototypes
	FactoryEntity* m_PFactory;

	//pools
	Pool<EntityMinion>* m_pMinionPool;

	//current entity on the screen
	std::vector<EntityMinion*> m_vCurrentEntities;
	std::vector<KiBlast*> m_vCurrentKiBlasts;
	std::vector<BeamWave*> m_vCurrentBeamWaves;
};
