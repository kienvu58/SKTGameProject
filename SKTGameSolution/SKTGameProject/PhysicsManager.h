#pragma once
#include <Box2D/Dynamics/b2World.h>
#include "ContactListener.h"

class PhysicsManager
{
public:
	~PhysicsManager();
	static PhysicsManager* GetInstance();
	static void DestroyInstance();
	void Init();
	b2World* GetWorld() const;
	void Update() const;
private:
	PhysicsManager();
	static PhysicsManager* s_Instance;
	b2World* m_World;
	ContactListener* m_pContactListener;
};

#define PhysicsMgr PhysicsManager::GetInstance()
