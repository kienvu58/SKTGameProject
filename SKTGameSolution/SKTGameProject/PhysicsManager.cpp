#include "PhysicsManager.h"
#include <Box2D/Common/b2Math.h>
#include "../GraphicsEngine/Globals.h"
#include "../Utilities/Math.h"
#include <Box2D/Collision/Shapes/b2EdgeShape.h>
#include <Box2D/Dynamics/b2Body.h>

PhysicsManager::PhysicsManager()
{
}

PhysicsManager::~PhysicsManager()
{
	delete m_World;
	delete m_pContactListener;
}

void PhysicsManager::Init()
{
	b2Vec2 gravity(0.0f, 0.0f);
	m_World = new b2World(gravity);

	//Init walls
	//create plain
	b2BodyDef plainDef;

	b2Body *plainBody = m_World->CreateBody(&plainDef);

	b2EdgeShape shape;

	// Floor
	shape.Set(b2Vec2(MetersFromPixels(-Globals::screenWidth) / 2, MetersFromPixels(-Globals::screenHeight) / 2),
		b2Vec2(MetersFromPixels(Globals::screenWidth) / 2, MetersFromPixels(-Globals::screenHeight) / 2));
	plainBody->CreateFixture(&shape, 1.0f);

	// Left wall
	shape.Set(b2Vec2(MetersFromPixels(-Globals::screenWidth) / 2, MetersFromPixels(Globals::screenHeight) / 2),
		b2Vec2(MetersFromPixels(-Globals::screenWidth) / 2, MetersFromPixels(-Globals::screenHeight) / 2));
	plainBody->CreateFixture(&shape, 1.0f);

	// Right wall
	shape.Set(b2Vec2(MetersFromPixels(Globals::screenWidth) / 2, MetersFromPixels(Globals::screenHeight) / 2),
		b2Vec2(MetersFromPixels(Globals::screenWidth) / 2, MetersFromPixels(-Globals::screenHeight) / 2));
	plainBody->CreateFixture(&shape, 1.0f);

	// Roof
	shape.Set(b2Vec2(MetersFromPixels(-Globals::screenWidth) / 2, MetersFromPixels(Globals::screenHeight) / 2),
		b2Vec2(MetersFromPixels(Globals::screenWidth) / 2, MetersFromPixels(Globals::screenHeight) / 2));
	plainBody->CreateFixture(&shape, 1.0f);

	//Init listener
	m_pContactListener = new ContactListener();
	m_World->SetContactListener(m_pContactListener);
}

b2World* PhysicsManager::GetWorld() const
{
	return m_World;
}

void PhysicsManager::Update() const
{
	m_World->Step(Globals::deltaTime, 20, 30);
}
