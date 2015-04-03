
// TestDlg.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTestDlgApp:
// See TestDlg.cpp for the implementation of this class
//

class IHandler;
class CSocketThread;
class CInerWorker;

class CTestDlgApp : public CWinApp
{
public:
	CTestDlgApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
private:
	HANDLE	m_hMutex;
	CSocketThread*	m_pSocket;
	CInerWorker*	m_pInerWorker;

public:
	inline CSocketThread* GetSocketThread() {return m_pSocket;}
	void SetInnerWorkHandler(IHandler* handler);
	DWORD GetInnerWorkThreadID();

public:
	virtual int ExitInstance();
};

extern CTestDlgApp theApp;

CTestDlgApp* GetTestApp();