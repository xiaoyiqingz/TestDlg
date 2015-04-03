#pragma once

#include <Windows.h>

/*
to test how to make ctitical_section to lock
*/

class CMyCritical
{
public:
	CMyCritical();
	~CMyCritical();

	void AcquireLock();
	void ReleaseLock();

private:
	static CRITICAL_SECTION m_cs;	
};