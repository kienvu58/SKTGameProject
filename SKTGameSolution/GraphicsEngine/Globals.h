#pragma once
#include <../Utilities/utilities.h>

class Globals
{
public:
	static const int screenWidth = 16*70;
	static const int screenHeight = 9*70;

	static const int TOUCH_ACTION_UP = 0;
	static const int TOUCH_ACTION_DOWN = 1;
	static const int TOUCH_ACTION_MOVE = 2;

	static const int animationTime = 8;
	static float deltaTime;

	static float scaleX;
	static float scaleY;

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