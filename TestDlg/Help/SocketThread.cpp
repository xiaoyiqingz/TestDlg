#include "StdAfx.h"
#include "SocketThread.h"
#include "ParseTransfer.h"

CSocketThread::CSocketThread(void)
	: CMyThread(NULL)
{
}


CSocketThread::~CSocketThread(void)
{
}

UINT CSocketThread::Run()
{
	/*int nCount = 5;
	while (nCount > 0) {
		TRACE(_T("%d\n"), nCount);	
		nCount--;
		Sleep(3000);
	}*/
	SOCKADDR_IN ClientAddr;

	// AddrLen  must be the length of SOCKADDR_IN
	int AddrLen = sizeof(SOCKADDR_IN);
	
	static char buf[MAX_PATH] = "\0";
	while (SOCKET newSocket = accept(ServerSocket, (SOCKADDR*)&ClientAddr, &AddrLen))
	{
		//m_pHandler->Post(buf);
		while (recv(newSocket, buf, MAX_PATH, 0)) {
			if (strlen(buf) > 0) {
				TCHAR szBuf[MAX_PATH] = _T("\0");
				MultiByteToWideChar(CP_UTF8, 0, buf, MAX_PATH, szBuf, MAX_PATH);
				HandleSocket((LPCTSTR)szBuf);
				strcpy_s(buf, "\0");
			}
		}
	}

	return 0;
}

void CSocketThread::InitSocket()
{
	ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN ServerAddr;
	ServerAddr.sin_family = AF_INET;
	//ServerAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	ServerAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	ServerAddr.sin_port = htons(8849);
	int ret =  bind(ServerSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr));
	if (ret != 0) {
		MessageBox(NULL, _T("bind socket failed"), NULL, MB_OK);
		return;
	}
	listen(ServerSocket, 5);
}

void CSocketThread::HandleSocket(CString strBuf)
{
	CParseTransfer Parse;
	Parse.PraseTransfer(strBuf);
}
