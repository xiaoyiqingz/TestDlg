#include "stdafx.h"
#include "MyCrtitcal.h"

CRITICAL_SECTION CMyCritical::m_cs;

CMyCritical::CMyCritical()
{
	InitializeCriticalSection(&m_cs);
}

CMyCritical::~CMyCritical()
{
	DeleteCriticalSection(&m_cs);
}

void CMyCritical::AcquireLock()
{
	EnterCriticalSection(&m_cs);
}

void CMyCritical::ReleaseLock()
{
	LeaveCriticalSection(&m_cs);
}

