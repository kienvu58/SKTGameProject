#pragma once
#include <Box2D/Dynamics/b2World.h>
#include "ContactListener.h"

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
