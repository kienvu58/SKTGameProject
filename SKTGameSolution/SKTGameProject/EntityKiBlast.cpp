#include "EntityKiBlast.h"
#include "SingletonClasses.h"
#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include "../GraphicsEngine/Globals.h"


EntityKiBlast::EntityKiBlast(): m_pBody(nullptr)
{
}

EntityKiBlast::EntityKiBlast(const EntityKiBlast& other) : m_b2PolygonShape(other.m_b2PolygonShape),
                                                           m_b2BodyDef(other.m_b2BodyDef),
                                                           m_b2FixtureDef(other.m_b2FixtureDef)
{
	m_iPrototypeId = other.m_iPrototypeId;
	InitBody(m_b2BodyDef, m_b2FixtureDef);
}

EntityKiBlast::~EntityKiBlast()
{
}

void EntityKiBlast::Update()
{
	if (IsActive())
	{
		auto isReversed = m_iDirection == -1;
		m_Sprite.SetRenderInfo(GraphicsFromPhysics(m_pBody->GetPosition()), isReversed);
		if (IsOutOfWall())
		{
			Dispatcher->DispatchMessageA(this, GameInstance, MSG_CLEAN_UP, this);
		}
	}
}

void EntityKiBlast::Render()
{
	if (IsActive())
	{
		m_Sprite.Render();
	}
}

Entity* EntityKiBlast::Clone()
{
	EntityKiBlast* newKiBlast = new EntityKiBlast(*this);

	return newKiBlast;
}

EntityType EntityKiBlast::GetType()
{
	return KI_BLAST;
}

bool EntityKiBlast::HandleMessage(const Telegram& telegram)
{
	return false;
}

void EntityKiBlast::InitSprite(int modelId, int frameId, int shaderId)
{
	m_Sprite.SetModel(ResourceMgr->GetModelById(modelId));
	m_Sprite.SetFrame(FrameMgr->GetFrameById(frameId));
	m_Sprite.SetShaders(ResourceMgr->GetShadersById(shaderId));
}

void EntityKiBlast::InitBody(const b2BodyDef& bodyDef, const b2FixtureDef& fixtureDef)
{
	m_pBody = PhysicsMgr->GetWorld()->CreateBody(&bodyDef);
	m_pBody->CreateFixture(&fixtureDef);
	m_pBody->SetBullet(true);
	m_pBody->SetUserData(this);
	m_pBody->SetActive(false);
}

void EntityKiBlast::Fire(b2Vec2 position, int direction)
{
	m_pBody->SetActive(true);
	m_pBody->SetTransform(position, m_pBody->GetAngle());
	m_pBody->SetLinearVelocity(m_fSpeed * b2Vec2(direction, 0));
	m_iDirection = direction;
}

void EntityKiBlast::Init(int prototypeId, const char* dataPath)
{

}

bool EntityKiBlast::IsActive()
{
	return m_pBody->IsActive();
}

void EntityKiBlast::SetSprite(Sprite sprite)
{
	m_Sprite = sprite;
}

void EntityKiBlast::SetSpeed(float speed)
{
	m_fSpeed = speed;
}

bool EntityKiBlast::IsOutOfWall() const
{
	float padding = 0.1;
	auto wallHalfWidth = MetersFromPixels(Globals::screenWidth) / 2;
	auto wallHalfHeight = MetersFromPixels(Globals::screenHeight) / 2;
	auto boundaryX = wallHalfWidth + padding;
	auto boundaryY = wallHalfHeight + padding;

	b2Vec2 position = m_pBody->GetPosition();

	auto outOfBoundaryX = abs(position.x) > boundaryX;
	auto outOfBoundaryY = abs(position.y) > boundaryY;

	return outOfBoundaryX || outOfBoundaryY;
}

b2Body* EntityKiBlast::GetBody() const
{
	return m_pBody;
}

float EntityKiBlast::Attack() const
{
	return m_fAttackDamage;
}
