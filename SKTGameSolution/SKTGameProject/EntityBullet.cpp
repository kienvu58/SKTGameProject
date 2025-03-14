#include "EntityBullet.h"


EntityBullet::EntityBullet(): m_fSpeed(0), m_fAttackDamage(0), m_iDirection(0)
{
}

EntityBullet::EntityBullet(const EntityBullet& other): m_fSpeed(other.m_fSpeed), m_fAttackDamage(other.m_fAttackDamage), m_iDirection(0)
{
}

EntityBullet::~EntityBullet()
{
}

void EntityBullet::Render()
{
}

void EntityBullet::Update()
{
}

bool EntityBullet::HandleMessage(const Telegram& telegram)
{
	return false;
}

EntityType EntityBullet::GetType()
{
	return {};
}

Entity* EntityBullet::Clone()
{
	return nullptr;
}

float EntityBullet::GetAttackDamage() const
{
	return m_fAttackDamage;
}
