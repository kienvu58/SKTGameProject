#include <json.hpp>
#include <fstream>
#include "EntityKiBlast.h"
#include "SingletonClasses.h"
#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include "../GraphicsEngine/Globals.h"


EntityKiBlast::EntityKiBlast(): m_pBody(nullptr), m_iExplosionPID(0)
{
}

EntityKiBlast::EntityKiBlast(const EntityKiBlast& other) : m_Sprite(other.m_Sprite),
                                                           m_b2PolygonShape(other.m_b2PolygonShape),
                                                           m_b2BodyDef(other.m_b2BodyDef),
                                                           m_b2FixtureDef(other.m_b2FixtureDef)
{
	m_fSpeed = other.m_fSpeed;
	m_fAttackDamage = other.m_fAttackDamage;
	m_iPrototypeId = other.m_iPrototypeId;
	InitBody(m_b2BodyDef, m_b2FixtureDef);
	m_pBody->SetUserData(this);
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
			m_bIsActive = false;
		}
	}
	else
	{
		Dispatcher->DispatchMessageA(this, GameInstance, MSG_CLEAN_UP, this);
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
	return ENTITY_KIBLAST;
}

bool EntityKiBlast::HandleMessage(const Telegram& telegram)
{
	if (telegram.Message == MSG_EXPLODE)
	{
		Explode();
		return true;
	}
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
	m_bIsActive = true;
	m_pBody->SetActive(true);
	m_pBody->SetTransform(position, m_pBody->GetAngle());
	m_pBody->SetLinearVelocity(m_fSpeed * b2Vec2(direction, 0));
	m_iDirection = direction;
}

void EntityKiBlast::Reset()
{
	m_bIsActive = false;
	m_pBody->SetActive(false);
}

void EntityKiBlast::Explode()
{
	// Create explosion effect here
	m_bIsActive = false;
}

void EntityKiBlast::Init(int prototypeId, const char* dataPath)
{
	m_iPrototypeId = prototypeId;

	std::ifstream fin(dataPath);
	nlohmann::json data(fin);
	fin.close();

	auto bodyData = data["physics"]["bodyDef"];
	auto fixtureData = data["physics"]["fixtureDef"];

	auto positionX = bodyData["position"]["x"].get<float>();
	auto positionY = bodyData["position"]["y"].get<float>();
	auto physicsPosition = b2Vec2(positionX, positionY);

	auto modelId = data["graphics"]["modelId"].get<int>();
	auto frameId = data["graphics"]["frameId"].get<int>();
	auto shaderId = data["graphics"]["shaderId"].get<int>();

	m_b2BodyDef.type = b2_dynamicBody;
	m_b2BodyDef.position = physicsPosition;

	auto boxHalfWidth = fixtureData["boxShape"]["hx"].get<float>();
	auto boxHalfHeight = fixtureData["boxShape"]["hy"].get<float>();
	m_b2PolygonShape.SetAsBox(boxHalfWidth, boxHalfHeight);

	m_b2FixtureDef.shape = &m_b2PolygonShape;
	m_b2FixtureDef.isSensor = true;
	m_b2FixtureDef.friction = fixtureData["friction"].get<float>();
	m_b2FixtureDef.restitution = fixtureData["restitution"].get<float>();
	m_b2FixtureDef.filter.categoryBits = fixtureData["filter"]["categoryBits"].get<int>();
	for (auto maskBits : fixtureData["filter"]["maskBits"])
	{
		m_b2FixtureDef.filter.maskBits |= maskBits.get<int>();
	}

	m_fAttackDamage = data["attackDamage"].get<float>();
	m_fSpeed = data["speed"].get<float>();

	InitSprite(modelId, frameId, shaderId);
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
	float padding = 1;
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
