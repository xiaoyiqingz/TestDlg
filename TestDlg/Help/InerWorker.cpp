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
ϵͳ��Ϊ�д��ڵ��߳̽�����Ϣ���С�����Ϣ���е��߳̾Ϳ��Խ�����Ϣ���������ǿ�����PostThreadMessage�������̷߳�����Ϣ��
û�д��ڵ��߳�ֻҪ������PeekMessage��GetMessage��ϵͳҲ��Ϊ��������Ϣ����
*/
UINT CInerWorker::Run()
{
	//ÿ��Ӧ�ó��򶼻������ÿ���߳̽���һ����Ϣ���У�������Ҫ���ľ��Ǵ������Ϣ������ȡ����Ϣ
	//�����ʱû�������봦�����Ϣ�� ��ô���Ǿ�����GetMessage��������̣߳����̹߳���
	MSG msg;
	PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);   //����һ����Ϣ����

	while(1) {
		GetMessage(&msg, NULL, 0, 0);   //����������Ϣ
		//GetMessage(&msg, NULL, WM_USER, WM_THREAD_PRINT); ֻ����USER->THREAD_PRINT����Ϣ
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
