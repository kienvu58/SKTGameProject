#include "EntityEffect.h"



EntityEffect::EntityEffect()
{
}


EntityEffect::~EntityEffect()
{
}


void EntityEffect::Render()
{
}

void EntityEffect::Update()
{
}

bool EntityEffect::HandleMessage(const Telegram& telegram)
{
	return false;
}

EntityType EntityEffect::GetType()
{
	return ENTITY_EFFECT;
}

Entity* EntityEffect::Clone()
{
	return nullptr;
}
