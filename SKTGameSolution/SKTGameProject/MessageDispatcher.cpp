#include "MessageDispatcher.h"
#include <iostream>


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

void MessageDispatcher::DispatchMessage(float delay, Entity* pSender, Entity* pReceiver, int msg, void* extraInfo)
{
	//make sure the receiver is valid
	if (pReceiver == nullptr)
	{
		return;
	}

	//create the telegram
	Telegram telegram(0, pSender, pReceiver, msg, extraInfo);

	//if there is no delay, route telegram immediately                       
	if (delay <= 0.0f)
	{
		//send the telegram to the recipient
		Discharge(pReceiver, telegram);
	}

	//else calculate the time when the telegram should be dispatched
	else
	{
		double CurrentTime = Clock->GetCurrentTime();

		telegram.DispatchTime = CurrentTime + delay;

		//and put it in the queue
		m_PriorityQ.insert(telegram);
	}
}

void MessageDispatcher::DispatchDelayedMessages()
{
	//get current time
	double CurrentTime = Clock->GetCurrentTime();

	//now peek at the queue to see if any telegrams need dispatching.
	//remove all telegrams from the front of the queue that have gone
	//past their sell by date
	while (!m_PriorityQ.empty() &&
		(m_PriorityQ.begin()->DispatchTime < CurrentTime) &&
		(m_PriorityQ.begin()->DispatchTime > 0))
	{
		//read the telegram from the front of the queue
		const Telegram& telegram = *m_PriorityQ.begin();

		Entity* pReceiver = telegram.pReceiver;

		//send the telegram to the recipient
		Discharge(pReceiver, telegram);

		//remove it from the queue
		m_PriorityQ.erase(m_PriorityQ.begin());
	}
}


MessageDispatcher::~MessageDispatcher()
{
}
