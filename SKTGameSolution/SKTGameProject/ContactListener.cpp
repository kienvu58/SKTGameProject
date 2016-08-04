#include "ContactListener.h"
#include "Box2D/Dynamics/Contacts/b2Contact.h"
#include "Entity.h"
#include <iostream>
#include "MessageTypes.h"
#include "SingletonClasses.h"

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

	if (bodyUserDataA && bodyUserDataB) {
		Entity* entityA = static_cast<Entity*>(bodyUserDataA);
		Entity* entityB = static_cast<Entity*>(bodyUserDataB);
		
		EntityType typeA = entityA->GetType();
		EntityType typeB = entityB->GetType();

		if (typeA == ENTITY_CELLJUNIOR && typeB == KI_BLAST)
		{
			float damage = dynamic_cast<KiBlast*>(entityB)->Attack();
			Dispatcher->DispatchMessageA(SEND_MSG_IMMEDIATELY, nullptr, entityA,
				MSG_MINION_TAKE_DAMAGE, (void*)&damage);
			Dispatcher->DispatchMessageA(SEND_MSG_IMMEDIATELY, nullptr, Singleton<Game>::GetInstance(),
				MSG_KIBLAST_OUT_OF_WALL, entityB);
		}

		if (typeA == KI_BLAST && typeB == ENTITY_CELLJUNIOR)
		{
			float damage = static_cast<KiBlast*>(entityA)->Attack();
			Dispatcher->DispatchMessageA(SEND_MSG_IMMEDIATELY, nullptr, entityB,
				MSG_MINION_TAKE_DAMAGE, (void*)&damage);
			Dispatcher->DispatchMessageA(SEND_MSG_IMMEDIATELY, nullptr, Singleton<Game>::GetInstance(),
				MSG_KIBLAST_OUT_OF_WALL, entityA);
		}

		if (typeA == ENTITY_CELLJUNIOR && typeB == ENTITY_PLAYER)
		{
			float damage = dynamic_cast<EntityMinion*>(entityA)->Attack();
			Dispatcher->DispatchMessageA(SEND_MSG_IMMEDIATELY, nullptr, entityB,
				MSG_PLAYER_TAKE_DAMAGE, (void*)&damage);
			Dispatcher->DispatchMessageA(SEND_MSG_IMMEDIATELY, nullptr, entityA,
				MSG_MINION_HIT_PLAYER, nullptr);
		}

		if (typeB == ENTITY_CELLJUNIOR && typeA == ENTITY_PLAYER)
		{
			float damage = dynamic_cast<EntityMinion*>(entityB)->Attack();
			Dispatcher->DispatchMessageA(SEND_MSG_IMMEDIATELY, nullptr, entityA,
				MSG_PLAYER_TAKE_DAMAGE, (void*)&damage);
			Dispatcher->DispatchMessageA(SEND_MSG_IMMEDIATELY, nullptr, entityB,
				MSG_MINION_HIT_PLAYER, nullptr);
		}
	}
}

void ContactListener::EndContact(b2Contact* contact)
{
//	std::cout << "End contact.\n";
}
