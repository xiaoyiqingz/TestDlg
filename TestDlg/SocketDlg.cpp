// SocketDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestDlg.h"
#include "SocketDlg.h"
#include "afxdialogex.h"


// CSocketDlg dialog

IMPLEMENT_DYNAMIC(CSocketDlg, CDialog)

CSocketDlg::CSocketDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSocketDlg::IDD, pParent) , m_socket(SOCKET_ERROR)
	, m_strSend(_T(""))
{

}

CSocketDlg::~CSocketDlg()
{
}

void CSocketDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ET_SEND, m_strSend);
}


BEGIN_MESSAGE_MAP(CSocketDlg, CDialog)
	ON_BN_CLICKED(IDC_BT_SEND, &CSocketDlg::OnBnClickedBtSend)
	ON_BN_CLICKED(IDC_BT_INIT, &CSocketDlg::OnBnClickedBtInit)
END_MESSAGE_MAP()


// CSocketDlg message handlers


void CSocketDlg::OnBnClickedBtInit()
{
	if (m_socket != SOCKET_ERROR)
		return;

	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_socket == SOCKET_ERROR) {
		MessageBox(_T("init socket error"));
	}

	SOCKADDR_IN ServerAddr;
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_addr.S_un.S_addr = inet_addr("192.168.250.1");
	ServerAddr.sin_port = htons(8848);

	int rec = connect(m_socket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr));
	if (rec == SOCKET_ERROR) {
		rec = WSAGetLastError();
		TRACE("%d", rec);

		MessageBox(_T("socket connect error"));
	}

}

void CSocketDlg::OnBnClickedBtSend()
{
	if (m_socket == SOCKET_ERROR) {
		MessageBox(_T("socket is null"));
	}
	
	UpdateData(TRUE);
	if (m_strSend.IsEmpty()) {
		MessageBox(_T("connect is null"));
	}

	char* buf = CT2A(m_strSend);
	int rec =  send(m_socket, buf, sizeof(buf), 0);
	if (rec == SOCKET_ERROR) {
		MessageBox(_T("send error"));
	}
}

