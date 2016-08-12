#pragma once
#include <Common/FSM/StateMachine.h>
#include "EntityLiving.h"
#include "EntityBeamWave.h"

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
	FIRING_ULTIMATE
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

	void Fire() const;
	void FireSpecial();
	void FireUltimate();

	float GetUltimateDuration() const;
	float GetSpecialDuration() const;
	
	void StopSpecial() const;
	void StopUltimate() const;


	void Reset() override;
private:
	//player attributes
	float m_fMaxKi;
	float m_fCurrentKi;
	float m_fVisionRange;
	float m_fVisionFreq;

	// prototypeIds of player's skills
	int m_iNormalPID;
	int m_iSpecialPID;
	int m_iUltimatePID;
	int m_iAuraPID;

	float m_fSpecialDuration;
	float m_fUltimateDuration;

	EntityBeamWave* m_pSpecial;
	EntityBeamWave* m_pUltimate;

	//State info
	StateMachine<EntityPlayer>* m_pStateMachine;
};
