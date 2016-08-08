#include "MessageDispatcher.h"
#include <iostream>
#include "SingletonClasses.h"


MessageDispatcher::MessageDispatcher()
{
}

void MessageDispatcher::Discharge(Entity* pReceiver, const Telegram& telegram)
{
	if (!pReceiver->HandleMessage(telegram))
	{
		//telegram could not be handled
		std::cout << "Message not handled";
	}
}

void MessageDispatcher::DispatchMessageA(Entity* pSender, Entity* pReceiver, MessageType msg, void* extraInfo)
{
	//make sure the receiver is valid
	if (pReceiver == nullptr)
	{
		return;
	}

	//create the telegram
	Telegram telegram(0, pSender, pReceiver, msg, extraInfo);

	//send the telegram to the recipient
	Discharge(pReceiver, telegram);
}


MessageDispatcher::~MessageDispatcher()
{
}
