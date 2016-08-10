#pragma once
#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include <vector>

class RayCastMultipleCallback :
	public b2RayCastCallback
{
public:
	RayCastMultipleCallback();
	~RayCastMultipleCallback();

	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) override;
	
	// only detect intersection with fixture in maskBits 
	int maskBits;

	// list of fixtures that intersect
	std::vector<b2Fixture*> fixtures;
};

