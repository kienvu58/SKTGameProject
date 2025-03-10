#pragma once
#include <Box2D/Common/b2Math.h>
#include "EntityMinion.h" 

class EntityMinion;
class SteeringBehavior
{
public:
	SteeringBehavior(EntityMinion* entity) :
		m_pOwner(entity),
		m_iFlags(0),
		m_fWanderJitter(50),
		m_fWanderRadius(0.1),
		m_fWanderDistance(15)
	{
		m_vWanderTarget.SetZero();
	};

	~SteeringBehavior();

	b2Vec2 Calculate();

	void SeekOn() { m_iFlags |= seek; }
	void SeekOff() { if (On(seek)) m_iFlags = m_iFlags &~seek; }
	void WanderOn() { m_iFlags |= wander; }
	void WanderOff() { if (On(wander)) m_iFlags = m_iFlags &~wander; }
	void FleeOn() { m_iFlags = m_iFlags |= flee; }
	void FleeOff() { if (On(flee)) m_iFlags = m_iFlags &~flee; }

	void SetSeekTarget(b2Vec2 target);
	void SetFleeTarget(b2Vec2 target);
private:
	enum behavior_type
	{
		none	= 0,
		seek	= 1 << 0,
		wander	= 1 << 1,
		flee	= 1 << 2
	};
	b2Vec2 m_vSteeringForce;
	EntityMinion* m_pOwner;
	int m_iFlags;

	b2Vec2 m_vSeekTarget;

	b2Vec2 m_vWanderTarget;
	float m_fWanderJitter;
	float m_fWanderRadius;
	float m_fWanderDistance;

	b2Vec2 m_vFleeTarget;

	bool On(behavior_type bt) const
	{ return (m_iFlags & bt) == bt; }

	b2Vec2 Seek(b2Vec2 TargetPos) const;
	b2Vec2 Wander();
	b2Vec2 Flee(b2Vec2 target) const;

	b2Vec2 CalculatePrioritized();
	bool AccumulateForce(b2Vec2 &totalForce, b2Vec2 forceToAdd) const;
};

