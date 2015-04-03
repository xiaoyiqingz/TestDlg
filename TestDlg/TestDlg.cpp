
// TestDlg.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "TestDlg.h"
#include "TestDlgDlg.h"
#include "Help/SocketThread.h"
#include "Help/InerWorker.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CTestDlgApp* GetTestApp()
{
	return (CTestDlgApp*)AfxGetApp();
}

// CTestDlgApp

BEGIN_MESSAGE_MAP(CTestDlgApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CTestDlgApp construction

CTestDlgApp::CTestDlgApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CTestDlgApp object

CTestDlgApp theApp;


// CTestDlgApp initialization

BOOL CTestDlgApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	HANDLE m_hMutex = CreateMutex(NULL, FALSE, _T("zisync"));
	WaitForSingleObject(m_hMutex, INFINITE);

	WSADATA wsaData;
	int ret =  WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (ret != 0) {
		 int nError =  WSAGetLastError();
		 MessageBox(NULL, _T("Initialize Socket failed!"), NULL, MB_OK);
		 return FALSE;
	}

	m_pSocket = new CSocketThread();
	m_pInerWorker = new CInerWorker(NULL);
	m_pInerWorker->Startup();

	CTestDlgDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Delete the shell manager created above.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}



int CTestDlgApp::ExitInstance()
{
	// TODO: Add your specialized code here and/or call the base class
	if (m_pSocket != NULL) {
		delete m_pSocket;
		m_pSocket = NULL;
	}

	if (m_pInerWorker != NULL) {
		delete m_pInerWorker;
		m_pInerWorker = NULL;
	}

	WSACleanup();
	ReleaseMutex(m_hMutex);
	CloseHandle(m_hMutex);
	return CWinApp::ExitInstance();
}

void CTestDlgApp::SetInnerWorkHandler(IHandler* handler)
{
	m_pInerWorker->SetHandler(handler);
}

DWORD CTestDlgApp::GetInnerWorkThreadID()
{
	return m_pInerWorker->GetThreadID();
}
