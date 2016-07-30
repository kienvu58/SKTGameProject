#pragma once
#pragma comment(lib, "winmm.lib")
#include "windows.h"

class CrudeTimer
{
public:
	CrudeTimer();
	~CrudeTimer();

	float GetCurrentTime();

private:
	// Set to the time (in seconds) when class is instantiated
	float m_fStartTime;
};