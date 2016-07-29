#pragma once
#pragma comment(lib, "winmm.lib")
#include "windows.h"

class CrudeTimer
{
public:
	~CrudeTimer();

	static CrudeTimer* GetInstance();

	float GetCurrentTime();
private:
	// Set the start time
	CrudeTimer();

	CrudeTimer(const CrudeTimer&);
	CrudeTimer& operator=(const CrudeTimer&);

	// Set to the time (in seconds) when class is instantiated
	float m_fStartTime;
};

#define Clock CrudeTimer::GetInstance()
