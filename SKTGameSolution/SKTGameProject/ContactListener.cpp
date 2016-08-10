#include "ContactListener.h"
#include "Box2D/Dynamics/Contacts/b2Contact.h"
#include "Entity.h"
#include <iostream>
#include "MessageTypes.h"
#include "SingletonClasses.h"
#include "EntityKiBlast.h"

ContactListener::ContactListener()
{
}


ContactListener::~ContactListener()
{
}

void ContactListener::BeginContact(b2Contact* contact)
{
	//	std::cout << "Begin contact.\n";
	void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

	if (bodyUserDataA && bodyUserDataB)
	{
		Entity* entityA = static_cast<Entity*>(bodyUserDataA);
		Entity* entityB = static_cast<Entity*>(bodyUserDataB);

		EntityType typeA = entityA->GetType();
		EntityType typeB = entityB->GetType();

		if (typeB == ENTITY_MINION && typeA == ENTITY_KIBLAST)
		{
			KiBlastHitsMinion(static_cast<EntityKiBlast*>(entityA), static_cast<EntityMinion*>(entityB));
		}

		if (typeA == ENTITY_MINION && typeB == ENTITY_KIBLAST)
		{
			KiBlastHitsMinion(static_cast<EntityKiBlast*>(entityB), static_cast<EntityMinion*>(entityA));
		}


//		if ((typeA == ENTITY_CELLJUNIOR ||
//			 typeA == ENTITY_CELL
//			) && typeB == ENTITY_PLAYER)
//		{
//			float damage = static_cast<EntityMinion*>(entityA)->GetAttackDamage();
//			Dispatcher->DispatchMessageA(nullptr, entityB, MSG_PLAYER_TAKE_DAMAGE, &damage);
//			Dispatcher->DispatchMessageA(nullptr, entityA, MSG_MINION_HIT_PLAYER, nullptr);
//		}
//
//		if ((typeB == ENTITY_CELLJUNIOR ||
//			 typeB == ENTITY_CELL) && typeA == ENTITY_PLAYER)
//		{
//			float damage = static_cast<EntityMinion*>(entityB)->GetAttackDamage();
//			Dispatcher->DispatchMessageA(nullptr, entityA, MSG_PLAYER_TAKE_DAMAGE, &damage);
//			Dispatcher->DispatchMessageA(nullptr, entityB, MSG_MINION_HIT_PLAYER, nullptr);
//		}
	}
}

void ContactListener::EndContact(b2Contact* contact)
{
	//	std::cout << "End contact.\n";
}

void ContactListener::KiBlastHitsMinion(EntityKiBlast* bullet, EntityMinion* minion)
{
	auto damage = static_cast<EntityBullet*>(bullet)->GetAttackDamage();
	Dispatcher->DispatchMessageA(nullptr, minion, MSG_MINION_TAKE_DAMAGE, &damage);
	Dispatcher->DispatchMessageA(nullptr, bullet, MSG_EXPLODE, nullptr);
	std::cout << "Hit" << std::endl;
}
