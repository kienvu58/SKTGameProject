#pragma once

#include "Telegram.h"
#include <set>
//#include "CrudeTimer.h"

const float SEND_MSG_IMMEDIATELY = 0.0f;
const auto NO_ADDITIONAL_INFO = nullptr;

class MessageDispatcher
{
public:
	MessageDispatcher();
	~MessageDispatcher();

	//send a message to another agent. Receiving agent is referenced by ID.
	void DispatchMessageA(float delay,
	                     Entity* pSender,
	                     Entity* pReceiver,
	                     MessageType msg,
	                     void* extraInfo);

	//send out any delayed messages. This method is called each time through   
	//the main game loop.
	void DispatchDelayedMessages();

private:
	//a std::set is used as the container for the delayed messages
	//because of the benefit of automatic sorting and avoidance
	//of duplicates. Messages are sorted by their dispatch time.
	std::set<Telegram> m_PriorityQ;

	//this method is utilized by DispatchMessage or DispatchDelayedMessages.
	//This method calls the message handling member function of the receiving
	//entity, pReceiver, with the newly created telegram
	static void Discharge(Entity* pReceiver, const Telegram& telegram);
};

