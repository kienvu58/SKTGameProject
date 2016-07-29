#include "CrudeTimer.h"


CrudeTimer::CrudeTimer()
{
	m_fStartTime = timeGetTime() * 0.001;
}


CrudeTimer::~CrudeTimer()
{
}

CrudeTimer* CrudeTimer::GetInstance()
{
	static CrudeTimer instance;
	return &instance;
}

float CrudeTimer::GetCurrentTime()
{
	return timeGetTime() - m_fStartTime;
}
