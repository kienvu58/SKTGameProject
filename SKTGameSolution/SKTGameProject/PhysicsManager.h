#pragma once
#include <Box2D/Dynamics/b2World.h>
#include "ContactListener.h"

enum CollisionCategory
{
	CATEGORY_WALL			= 1 << 0,
	CATEGORY_PLAYER			= 1 << 1,
	CATEGORY_CELL			= 1 << 2,
	CATEGORY_YELLOW_KIBLAST		= 1 << 3,
	CATEGORY_CELLJUNIOR	= 1 << 4,
	CATEGORY_GREEN_KIBLAST  = 1 << 5
};

class PhysicsManager
{
public:
	PhysicsManager();
	~PhysicsManager();

	void Init();
	b2World* GetWorld() const;
	void Update() const;
private:
	b2World* m_World;
	ContactListener* m_pContactListener;
};
