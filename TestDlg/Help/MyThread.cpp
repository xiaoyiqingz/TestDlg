#include "stdafx.h"
#include "MyThread.h"

CMyThread::CMyThread(IHandler* handler)
	: m_pThread(NULL), m_pHandler(handler)
{
	m_pThread = AfxBeginThread(ThreadEntry, this, 0, 0U, CREATE_SUSPENDED);
	m_pThread->m_bAutoDelete = FALSE;
}

CMyThread::~CMyThread()
{
	if (m_pThread != NULL) {
		WaitForSingleObject(m_pThread->m_hThread, INFINITE);
		delete m_pThread;
		m_pThread = NULL;
	}

	if (m_pHandler != NULL) {
		delete m_pHandler;
		m_pHandler = NULL;
	}
}

UINT CMyThread::Run()
{
	return 0;
}

BOOL CMyThread::Startup()
{
	m_pThread->ResumeThread();
	return TRUE;
}

UINT AFX_CDECL CMyThread::ThreadEntry(LPVOID lpParam)
{
 	return ((CMyThread*)lpParam)->Run();
}

DWORD CMyThread::GetThreadID()
{
	return m_pThread->m_nThreadID;
}

void CMyThread::SetHandler(IHandler* handler) 
{
	m_pHandler = handler;
}

UIHandler::UIHandler(HWND hWnd)
	: m_hWnd(hWnd)
{
}

UIHandler::~UIHandler()
{

}

void UIHandler::Post(LPVOID lpParam)
{
	if (m_hWnd != NULL) {
		::PostMessage(m_hWnd, WM_HANDLER, 0, (LPARAM)lpParam);
	}
}
