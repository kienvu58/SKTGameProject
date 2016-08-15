#pragma once
#include <Common/FSM/StateMachine.h>
#include "EntityLiving.h"
#include "EntityBeamWave.h"
#include "EntityBarrier.h"

enum AnimationName
{
	STANDING,
	MOVING_FORWARD,
	MOVING_BACKWARD,
	MOVING_UP,
	MOVING_DOWN,
	TAKING_DAMAGED,
	FALLING,
	DEAD,
	FIRING,
	FIRING_SPECIAL,
	FIRING_ULTIMATE,
	CHARGING
};

class EntityPlayer :
	public EntityLiving
{
public:
	EntityPlayer();
	~EntityPlayer();

	void Render() override;
	void Update() override;
	EntityType GetType() override;
	bool HandleMessage(const Telegram& telegram) override;

	//Get FSM
	StateMachine<EntityPlayer>* GetFSM() const;

	//clone
	EntityLiving* Clone() override;

	void Init(int prototypeId, const char* dataPath) override;

	bool IsOnTheGround() const;
	void DetectMinions();

	void DecreaseKi(float amount);
	void Fire() const;
	void FireSpecial();
	void FireUltimate();

	void StopSpecial() const;
	void StopUltimate() const;

	float GetNormalSkillCost() const;
	float GetSpecialSkillCost() const;
	float GetUltimateSkillCost() const;

	void Reset() override;
	float GetCurrentKi() const;
	float GetMaxKi() const;

	void InCreaseCantDieTime(float amount);
	void DeCreaseCantDieTime(float amnout);
	bool IsCantDie() const;
	void ResetCantDieTime();

	void StopCharging() const;
	void Charge();

private:
	//player attributes
	float m_fMaxKi;
	float m_fCurrentKi;
	float m_fVisionRange;
	float m_fVisionFreq;
	float m_fCurrentCantDieCount;
	float m_fMaxCantDieTime;
	bool m_bIsCantDie;

	// prototypeIds of player's skills
	int m_iNormalPID;
	int m_iSpecialPID;
	int m_iUltimatePID;
	int m_iAuraPID;

	EntityEffect* m_pAura;
	EntityBeamWave* m_pSpecial;
	EntityBarrier* m_pUltimate;
	float m_fNormalCost;
	float m_fSpecialCost;
	float m_fUltimateCost;

	//State info
	StateMachine<EntityPlayer>* m_pStateMachine;
};
