#include "RayCastMultipleCallback.h"
#include <Box2D/Dynamics/b2Fixture.h>


RayCastMultipleCallback::RayCastMultipleCallback(): maskBits(0) {
}


RayCastMultipleCallback::~RayCastMultipleCallback()
{
}

float32 RayCastMultipleCallback::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
{
	auto categoryBits = fixture->GetFilterData().categoryBits;
	if (categoryBits & maskBits)
	{
		fixtures.push_back(fixture);
		return 1;
	}
	return -1;
}
