#pragma once
#include "Entity.h"
#include "MessageTypes.h"

class Telegram
{
public:
	Telegram();
	Telegram(float time, Entity* sender, Entity* receiver, MessageType message, void* info = nullptr);
	~Telegram();

	// the pointer point to entity that send this telegram
	Entity* pSender;

	// the pointer point to entity that receive this telegram
	Entity* pReceiver;

	// the message itself. These are all enumurated in the file "MessageTypes.h"
	int Message;

	// messages can be dispatched immediately or delayed for a specified amount
	// of time. If a delay is necessary this field is stamped with the time 
	// the message should be dispatched.
	float DispatchTime;

	//any additional information that may accompany the message
	void* ExtraInfo;

	//these telegrams will be stored in a priority queue. Therefore the >
	//operator needs to be overloaded so that the PQ can sort the telegrams
	//by time priority. Note how the times must be smaller than

	friend bool operator == (const Telegram& t1, const Telegram& t2);

	friend bool operator < (const Telegram& t1, const Telegram& t2);

};

//handy helper function for dereferencing the ExtraInfo field of the Telegram 
//to the required type.
template <class T>
T DereferenceToType(void* p)
{
	return *static_cast<T*>(p);
}

