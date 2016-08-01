#pragma once
#include <Box2D/Dynamics/b2World.h>
#include "ContactListener.h"

enum CollisionCategory
{
	CATEGORY_WALL		= 1 << 0,
	CATEGORY_PLAYER		= 1 << 1,
	CATEGORY_MINION		= 1 << 2,
	CATEGORY_KI_BLAST	= 1 << 3
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
