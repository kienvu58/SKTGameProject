#include "SteeringBehavior.h"
#include <ctime>
#include <cstdlib>

SteeringBehavior::~SteeringBehavior()
{
}

b2Vec2 SteeringBehavior::Calculate()
{
	m_vSteeringForce.SetZero();
	return CalculatePrioritized();
}

void SteeringBehavior::SetSeekTarget(b2Vec2 target)
{
	m_vSeekTarget = target;
}

b2Vec2 SteeringBehavior::Seek(b2Vec2 TargetPos) const
{
	b2Vec2 position = m_pOwner->GetBody()->GetPosition();
	b2Vec2 desiredVector = TargetPos - position;
	return desiredVector;
}

b2Vec2 SteeringBehavior::Wander()
{
	if (m_pOwner->GetBody()->GetLinearVelocity().Length() > 0)
	{
		int r1 = rand();
		int r2 = rand();
		int r3 = rand();
		int r4 = rand();

		m_vWanderTarget += b2Vec2(
			m_fWanderJitter * (r1 - r2) * 1.f / RAND_MAX,
			m_fWanderJitter * (r3 - r4) * 1.f / RAND_MAX
		);

		m_vWanderTarget.Normalize();
		m_vWanderTarget *= m_fWanderRadius;

		b2Vec2 target = m_vWanderTarget + b2Vec2(m_fWanderDistance, 0);

		b2Vec2 headingVector = m_pOwner->GetBody()->GetLinearVelocity();
		headingVector.Normalize();

		b2Vec2 sideVector;
		sideVector.y = headingVector.x;
		sideVector.x = -headingVector.y;

		Matrix magicMatrix;

		//row 1
		magicMatrix.m[0][0] = headingVector.x;
		magicMatrix.m[0][1] = headingVector.y;
		magicMatrix.m[0][2] = 0;
		magicMatrix.m[0][3] = 0;

		//row 2
		magicMatrix.m[1][0] = sideVector.x;
		magicMatrix.m[1][1] = sideVector.y;
		magicMatrix.m[1][2] = 0;
		magicMatrix.m[1][3] = 0;

		//row 3
		magicMatrix.m[2][0] = 0;
		magicMatrix.m[2][1] = 0;
		magicMatrix.m[2][2] = 0;
		magicMatrix.m[2][3] = 0;

		//row 2
		magicMatrix.m[3][0] = m_pOwner->GetBody()->GetPosition().x;
		magicMatrix.m[3][1] = m_pOwner->GetBody()->GetPosition().y;
		magicMatrix.m[3][2] = 0;
		magicMatrix.m[3][3] = 1;

		Vector4 targetInWorld;
		targetInWorld = Vector4(target.x, target.y, 0, 1)*magicMatrix;

		b2Vec2 currentPosition = m_pOwner->GetBody()->GetPosition();
		b2Vec2 currentVelocity = m_pOwner->GetBody()->GetLinearVelocity();
		
		b2Vec2 force = b2Vec2(targetInWorld.x, targetInWorld.y)
			- currentPosition;
		b2Vec2 desiredVector = currentVelocity + force;

		return desiredVector;
	}
	return b2Vec2();
}

b2Vec2 SteeringBehavior::CalculatePrioritized()
{
	b2Vec2 force;
	if (On(seek))
	{
		force = Seek(m_vSeekTarget);
		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	}
	if (On(flee))
	{
		force = Flee(m_vFleeTarget);
		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	}
	if (On(wander))
	{
		force = Wander();
		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	}
	return m_vSteeringForce;
}

bool SteeringBehavior::AccumulateForce(b2Vec2& runningTotalForce, b2Vec2 forceToAdd) const
{
	runningTotalForce += forceToAdd;
	b2Vec2 currentVelocity = m_pOwner->GetBody()->GetLinearVelocity();
	if (runningTotalForce.Length() != 0)
	{
		runningTotalForce.Normalize();
		runningTotalForce *= currentVelocity.Length();
		runningTotalForce -= currentVelocity;
	}
	return true;
	/*//calculate how much steering force the entity has used so far
	float magnitudeSoFar = runningTotalForce.Length();

	//calculate how much steering force remains to be used by this entity
	float magnitudeRemaining = m_pOwner->GetMaxForce() - magnitudeSoFar;

	if (magnitudeRemaining <= 0.0) return false;

	float magnitudeToAdd = forceToAdd.Length();

	if (magnitudeToAdd < magnitudeRemaining)
	{
		runningTotalForce += forceToAdd;
	}else
	{
		b2Vec2 add = forceToAdd;
		add.Normalize();
		add *= magnitudeRemaining;
		runningTotalForce += add;
	}*/
}

void SteeringBehavior::SetFleeTarget(b2Vec2 target)
{
	m_vFleeTarget = target;
}

b2Vec2 SteeringBehavior::Flee(b2Vec2 target) const
{
	b2Vec2 currentPosition = m_pOwner->GetBody()->GetPosition();
	b2Vec2 desiredVector = currentPosition - m_vFleeTarget;
	return desiredVector;
}
