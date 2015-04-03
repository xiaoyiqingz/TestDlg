#pragma once
#include "Help/MyThread.h"

class CSocketThread : public CMyThread
{
public:
	CSocketThread(void);
	~CSocketThread(void);

	virtual UINT Run();
	void InitSocket();

private: 
	SOCKET	ServerSocket;
};

