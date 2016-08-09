#include "EntityBullet.h"



EntityBullet::EntityBullet()
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
