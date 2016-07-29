#include "ContactListener.h"
#include <iostream>

ContactListener::ContactListener()
{
}


ContactListener::~ContactListener()
{
}

void ContactListener::BeginContact(b2Contact* contact)
{
	std::cout << "Begin contact.\n";
}

void ContactListener::EndContact(b2Contact* contact)
{
	std::cout << "End contact.\n";
}
