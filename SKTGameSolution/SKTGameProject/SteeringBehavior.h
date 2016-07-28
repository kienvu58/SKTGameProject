#pragma once
#include <Box2D/Common/b2Math.h>
#include "EntityLiving.h"

class SteeringBehavior
{
public:
	SteeringBehavior(EntityLiving *entity) :
		m_pOwner(entity),
		m_iFlags(0),
		m_fWanderRadius(8),
		m_fWanderDistance(8),
		m_fWanderJitter(2)
	{};
	~SteeringBehavior();

	b2Vec2 Calculate();

	void SeekOn() { m_iFlags |= seek; }
	void SeekOff() { if (On(seek)) m_iFlags = m_iFlags &~seek; }
	void WanderOn() { m_iFlags |= wander; }
	void WanderOff() { if (On(wander)) m_iFlags = m_iFlags &~wander; }
private:
	enum behavior_type
	{
		none	= 0,
		seek	= 1 << 0,
		wander	= 1 << 1
	};
	b2Vec2 m_vSteeringForce;
	EntityLiving* m_pOwner;
	int m_iFlags;

	b2Vec2 m_vWanderTarget;
	float m_fWanderJitter;
	float m_fWanderRadius;
	float m_fWanderDistance;

	bool On(behavior_type bt) { return (m_iFlags & bt) == bt; }
	b2Vec2 Seek(b2Vec2 TargetPos);
	b2Vec2 Wander();
	b2Vec2 CalculatePrioritized();

	bool AccumulateForce(b2Vec2 &totalForce, b2Vec2 forceToAdd);
};

