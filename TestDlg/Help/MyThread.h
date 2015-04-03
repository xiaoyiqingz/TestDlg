#pragma once

#include "UserMsg.h"

class IHandler
{
public:
	virtual ~IHandler(){};
	virtual void Post(LPVOID lpParam) = 0;
};

class UIHandler : public IHandler
{
public:
	UIHandler(HWND hWnd);
	~UIHandler();

	virtual void Post(LPVOID lpParam);

private: 
	HWND m_hWnd;
};

class IRunable
{
public:
	virtual ~IRunable(){};
	virtual UINT Run() = 0;
};

class CMyThread : public IRunable
{
public:
	CMyThread(IHandler* handler);
	virtual ~CMyThread();

	virtual UINT Run();
	static UINT AFX_CDECL ThreadEntry(LPVOID lpParam);
	BOOL Startup();
	DWORD GetThreadID();
	void SetHandler(IHandler* handler);

protected:
	IHandler*	 m_pHandler;
private:
	CWinThread*  m_pThread;
};