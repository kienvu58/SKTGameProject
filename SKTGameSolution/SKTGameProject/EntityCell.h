#pragma once
#include "EntityMinion.h"
#include <Common/FSM/StateMachine.h>

enum CellAnimationName
{
	CELL_STANDING,
	CELL_FORWARD,
	CELL_BACKWARD,
	CELL_UP,
	CELL_DOWN,
	CELL_FIRING
};

float const MAX_DODGING_OVERHEAT = 100;
float const MIN_DODGING_OVERHEAT = 0;

class EntityCell
	: public EntityMinion
{
public:
	void InitStateMachine();
	EntityCell();
	~EntityCell();

	//Get FSM
	StateMachine<EntityCell>* GetFSM() const;
	
	void Init(int prototypeId, const char* dataPath) override;

	//clone
	Entity* Clone() override;

	void Update() override;
	bool HandleMessage(const Telegram& telegram) override;

	void Reset() override;

	//battle
	void Fire() const;
	void IncreaseDodgingOverHeat(float amount);
	void DecreaseDodgingOverHeat(float amount);
	bool IsDodgingOverHeated() const;
private:
	//State info
	StateMachine<EntityCell>* m_pStateMachine;

	//Skill prototype ids.
	int m_iGreenKiBlastID;

	float m_fCurrentDodgingOverheat;
	bool m_bIsDodgingOverheatd;
};

