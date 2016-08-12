#pragma once
#include <../Utilities/Math.h>
class Globals
{
public:
	static const int screenWidth = 16*70;
	static const int screenHeight = 9*70;

	static const int animationTime = 8;
	static float deltaTime;

	static bool IsOutOfBoundary(Vector2 position, float padding)
	{
		auto wallHalfWidth = float(Globals::screenWidth) / 2;
		auto wallHalfHeight = float(Globals::screenHeight) / 2;
		auto boundaryX = wallHalfWidth + padding;
		auto boundaryY = wallHalfHeight + padding;

		auto outOfBoundaryX = fabsf(position.x) > boundaryX;
		auto outOfBoundaryY = fabsf(position.y) > boundaryY;

		return outOfBoundaryX || outOfBoundaryY;
	}
};