#include "StdAfx.h"
#include "SocketThread.h"

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
	
	SOCKET newSocket = accept(ServerSocket, (SOCKADDR*)&ClientAddr, &AddrLen);

	static char buf[MAX_PATH] = "\0";
	while (TRUE)
	{
		//m_pHandler->Post(buf);
		recv(newSocket, buf, MAX_PATH, 0);
		if (strlen(buf) > 0) {
			TRACE(buf);
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
