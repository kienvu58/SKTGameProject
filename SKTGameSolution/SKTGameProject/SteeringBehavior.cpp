#include "SteeringBehavior.h"
#include <ctime>

SteeringBehavior::~SteeringBehavior()
{
}

b2Vec2 SteeringBehavior::Calculate()
{
	m_vSteeringForce.SetZero();
	return CalculatePrioritized();
}

b2Vec2 SteeringBehavior::Seek(b2Vec2 TargetPos)
{
	b2Vec2 position = m_pOwner->GetBody()->GetPosition();
	b2Vec2 DesiredVector = TargetPos - position;
	DesiredVector.Normalize();
	DesiredVector *= 5;
	return DesiredVector - m_pOwner->GetBody()->GetLinearVelocity();
}

b2Vec2 SteeringBehavior::Wander()
{
	srand(time(0));
	if (m_pOwner->GetBody()->GetLinearVelocity().Length() > 0)
	{
		m_vWanderTarget += b2Vec2(
			m_fWanderJitter * (rand() - rand()) / RAND_MAX,
			m_fWanderJitter * (rand() - rand()) / RAND_MAX
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
		targetInWorld = magicMatrix * Vector4(target.x, target.y, 0, 1);

		return b2Vec2(targetInWorld.x, targetInWorld.y)
			- m_pOwner->GetBody()->GetPosition();

	}
	return b2Vec2();
}

b2Vec2 SteeringBehavior::CalculatePrioritized()
{
	b2Vec2 force;
	if (On(seek))
	{
		force = Seek(b2Vec2(-5.0f, -4.0f));
		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	}
	if (On(wander))
	{
		force = Wander();
		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
	}
	return m_vSteeringForce;
}

bool SteeringBehavior::AccumulateForce(b2Vec2& runningTotalForce, b2Vec2 forceToAdd)
{
	//calculate how much steering force the entity has used so far
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
	}
	return true;
}
