#pragma once

#include "Help/MyThread.h"

class CInerWorker : public CMyThread
{
public:
	CInerWorker(IHandler* handler);
	~CInerWorker(void);

	virtual UINT Run();

private:
	void OnHandlePrint(LPVOID lpParam);
};

