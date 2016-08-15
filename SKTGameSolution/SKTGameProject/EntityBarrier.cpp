#include <json.hpp>
#include <fstream>
#include "EntityBarrier.h"
#include "SingletonClasses.h"


EntityBarrier::EntityBarrier(): m_pBody(nullptr), m_pBarrierEffect(nullptr), m_iBarrierEffectPID(0)
{
}

EntityBarrier::EntityBarrier(const EntityBarrier& other): m_pBarrierEffect(nullptr),
                                                          m_iBarrierEffectPID(other.m_iBarrierEffectPID),
                                                          m_b2CircleShape(other.m_b2CircleShape),
                                                          m_b2BodyDef(other.m_b2BodyDef),
                                                          m_b2FixtureDef(other.m_b2FixtureDef)
{
	m_iPrototypeId = other.m_iPrototypeId;
	InitBody(m_b2BodyDef, m_b2FixtureDef);
}

EntityBarrier::~EntityBarrier()
{
}

void EntityBarrier::InitBody(const b2BodyDef& bodyDef, const b2FixtureDef& fixtureDef)
{
	m_pBody = PhysicsMgr->GetWorld()->CreateBody(&bodyDef);
	m_pBody->CreateFixture(&fixtureDef);
	m_pBody->SetUserData(this);
	m_pBody->SetActive(false);
}

void EntityBarrier::Render()
{
	if (IsActive())
	{
		if (m_pBarrierEffect)
			m_pBarrierEffect->Render();
	}
}

void EntityBarrier::Update()
{
	if (IsActive())
	{
		if (m_pBarrierEffect)
			m_pBarrierEffect->Update();
	}
	else
	{
		Reset();
	}
}

bool EntityBarrier::HandleMessage(const Telegram& telegram)
{
	return false;
}

Entity* EntityBarrier::Clone()
{
	auto clone = new EntityBarrier(*this);
	return clone;
}

EntityType EntityBarrier::GetType()
{
	return ENTITY_BARRIER;
}

void EntityBarrier::Init(int prototypeId, const char* dataPath)
{
	std::ifstream fin(dataPath);
	nlohmann::json data(fin);
	fin.close();

	auto radius = MetersFromPixels(data["radiusInPixels"].get<int>());

	m_b2BodyDef.type = b2_dynamicBody;
	m_b2CircleShape.m_p.SetZero();
	m_b2CircleShape.m_radius = radius;
	m_b2FixtureDef.shape = &m_b2CircleShape;
	m_b2FixtureDef.isSensor = true;
	m_b2FixtureDef.filter.categoryBits = data["filter"]["categoryBits"].get<int>();
	m_b2FixtureDef.filter.maskBits = 0;
	for (auto maskBits : data["filter"]["maskBits"])
	{
		m_b2FixtureDef.filter.maskBits |= maskBits.get<int>();
	}
	m_iBarrierEffectPID = data["barrierEffectPID"].get<int>();
	InitBody(m_b2BodyDef, m_b2FixtureDef);
}

void EntityBarrier::Reset()
{
	m_pBody->SetActive(false);
}

void EntityBarrier::Activate(b2Vec2 position)
{
	m_bIsActive = true;
	m_pBody->SetActive(true);
	m_pBody->SetTransform(position, 0);
	if (!m_pBarrierEffect)
		m_pBarrierEffect = static_cast<EntityEffect*>(PoolMgr->GetEntityByPrototypeId(m_iBarrierEffectPID));
	m_pBarrierEffect->Start(position, this);
}

void EntityBarrier::Stop()
{
	m_bIsActive = false;
	m_pBarrierEffect->Stop();
	m_pBarrierEffect->ResetCurrentAnimationInfo();
}
