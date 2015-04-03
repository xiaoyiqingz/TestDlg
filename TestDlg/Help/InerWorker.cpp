#include "StdAfx.h"
#include "InerWorker.h"
#include "UserMsg.h"

CInerWorker::CInerWorker(IHandler* handler)
	: CMyThread(handler)
{
}


CInerWorker::~CInerWorker(void)
{
}

/*
系统会为有窗口的线程建立消息队列。有消息队列的线程就可以接收消息，例如我们可以用PostThreadMessage函数向线程发送消息。
没有窗口的线程只要调用了PeekMessage或GetMessage，系统也会为它创建消息队列
*/
UINT CInerWorker::Run()
{
	//每个应用程序都会给它的每个线程建立一个消息队列，我们需要做的就是从这个消息队列中取出消息
	//如果此时没有我们想处理的消息， 那么我们就利用GetMessage阻塞这个线程，将线程挂起
	MSG msg;
	PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);   //创建一个消息队列

	while(1) {
		GetMessage(&msg, NULL, 0, 0);   //接收所有消息
		//GetMessage(&msg, NULL, WM_USER, WM_THREAD_PRINT); 只接收USER->THREAD_PRINT的消息
		switch(msg.message) {
		case  WM_THREAD_QUIT:
			return 1;
		case  WM_THREAD_PRINT:			
			OnHandlePrint((LPVOID)msg.lParam);
			break;
		}
	}
	Sleep(10000);
	return 0;
}

void CInerWorker::OnHandlePrint(LPVOID lpParam)
{
	TCHAR* szReq = static_cast<TCHAR*>(lpParam);
	OutputDebugString(szReq);
	
	if (m_pHandler != NULL) {
		m_pHandler->Post(szReq);
	}	
}
