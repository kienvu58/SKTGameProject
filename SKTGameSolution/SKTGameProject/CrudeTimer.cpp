#include "CrudeTimer.h"


CrudeTimer::CrudeTimer()
{
	m_fStartTime = timeGetTime() * 0.001f;
}


CrudeTimer::~CrudeTimer()
{
}


float CrudeTimer::GetCurrentTime()
{
	return timeGetTime() - m_fStartTime;
}
