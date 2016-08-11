#pragma once

#include "Telegram.h"

class MessageDispatcher
{
public:
	MessageDispatcher();
	~MessageDispatcher();

	//send a message to another agent. Receiving agent is referenced by ID.
	static void DispatchMessageA(Entity* pSender,
	                      Entity* pReceiver,
	                      MessageType msg,
	                      void* extraInfo);

private:
	//this method is utilized by DispatchMessage or DispatchDelayedMessages.
	//This method calls the message handling member function of the receiving
	//entity, pReceiver, with the newly created telegram
	static void Discharge(Entity* pReceiver, const Telegram& telegram);
};
