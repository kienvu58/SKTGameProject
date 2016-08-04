#include "Telegram.h"
#include <cmath>

//SmallestDelay apart before two Telegrams are considered unique.
const double SmallestDelay = 0.025;

Telegram::Telegram(): pSender(nullptr), pReceiver(nullptr), Message(), DispatchTime(-1), ExtraInfo(nullptr)
{
}

Telegram::Telegram(float time, Entity* sender, Entity* receiver, MessageType message, void* info)
	: pSender(sender),
	  pReceiver(receiver),
	  Message(message),
	  DispatchTime(time),
	  ExtraInfo(info)
{
}

Telegram::~Telegram()
{
}


bool operator==(const Telegram& t1, const Telegram& t2)
{
	return fabs(t1.DispatchTime - t2.DispatchTime) < SmallestDelay &&
		t1.pSender == t2.pSender &&
		t1.pReceiver == t2.pReceiver &&
		t1.Message == t2.Message &&
		t1.ExtraInfo == t2.ExtraInfo;
}

bool operator<(const Telegram& t1, const Telegram& t2)
{
	if (t1 == t2) return false;
	return (t1.DispatchTime < t2.DispatchTime);
}
