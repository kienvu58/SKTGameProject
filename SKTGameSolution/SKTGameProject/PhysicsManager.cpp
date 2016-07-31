#include "PhysicsManager.h"
#include <Box2D/Common/b2Math.h>
#include "../GraphicsEngine/Globals.h"
#include "../Utilities/Math.h"
#include <Box2D/Collision/Shapes/b2EdgeShape.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>

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
	b2FixtureDef fixture;

	fixture.shape = &shape;
	fixture.filter.groupIndex = -1;
	// Floor
	shape.Set(b2Vec2(MetersFromPixels(-Globals::screenWidth) / 2, MetersFromPixels(-Globals::screenHeight) / 2),
		b2Vec2(MetersFromPixels(Globals::screenWidth) / 2, MetersFromPixels(-Globals::screenHeight) / 2));
	plainBody->CreateFixture(&fixture);

	// Left wall
	shape.Set(b2Vec2(MetersFromPixels(-Globals::screenWidth) / 2, MetersFromPixels(Globals::screenHeight) / 2),
		b2Vec2(MetersFromPixels(-Globals::screenWidth) / 2, MetersFromPixels(-Globals::screenHeight) / 2));
	plainBody->CreateFixture(&fixture);

	// Right wall
	shape.Set(b2Vec2(MetersFromPixels(Globals::screenWidth) / 2, MetersFromPixels(Globals::screenHeight) / 2),
		b2Vec2(MetersFromPixels(Globals::screenWidth) / 2, MetersFromPixels(-Globals::screenHeight) / 2));
	plainBody->CreateFixture(&fixture);

	// Roof
	shape.Set(b2Vec2(MetersFromPixels(-Globals::screenWidth) / 2, MetersFromPixels(Globals::screenHeight) / 2),
		b2Vec2(MetersFromPixels(Globals::screenWidth) / 2, MetersFromPixels(Globals::screenHeight) / 2));
	plainBody->CreateFixture(&fixture);

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
