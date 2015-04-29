
// TestDlgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestDlg.h"
#include "TestDlgDlg.h"
#include "afxdialogex.h"
#include "Help/MyThread.h"
#include "Help/SocketThread.h"
#include "UserMsg.h"

#include "SocketDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About

BOOL DirName(LPTSTR tpath, TCHAR tpath_seprator = _T('\\'))
{
	TCHAR* p = _tcsrchr(tpath, tpath_seprator);
	if (p == NULL) {
		return FALSE;
	}

	if (p == tpath) {									// \foo
		*(p + 1) = _T('\0');
		return TRUE;
	} 

	if (p == (tpath + 2) && tpath[1] == _T(':')) {	// X:\foo
		*(p + 1) = _T('\0');
		return TRUE;
	}

	*p = _T('\0');
	return TRUE;
}

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTestDlgDlg dialog


UINT AFX_CDECL CTestDlgDlg::ThreadCheckFunc(LPVOID pParam)
{
	CTestDlgDlg* pTestDlg = (CTestDlgDlg*)pParam;

	while (1) {
		WaitForSingleObject(pTestDlg->m_event, INFINITE);
		pTestDlg->TestCriticalSection();
	}

	return 0;
}

CTestDlgDlg::CTestDlgDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestDlgDlg::IDD, pParent)
	, m_string(_T("")) ,m_event(FALSE, FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_string);
}

BEGIN_MESSAGE_MAP(CTestDlgDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTestDlgDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTestDlgDlg::OnBnClickedButton2)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON3, &CTestDlgDlg::OnBnClickedButton3)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON4, &CTestDlgDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CTestDlgDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CTestDlgDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON8, &CTestDlgDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON7, &CTestDlgDlg::OnBnClickedButton7)
	ON_MESSAGE(WM_TEST, OnMsgTest)
	ON_BN_CLICKED(IDC_BUTTON9, &CTestDlgDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CTestDlgDlg::OnBnClickedButton10)
	ON_MESSAGE(WM_HANDLER, OnMessageHandler)
	ON_BN_CLICKED(IDC_BUTTON11, &CTestDlgDlg::OnBnClickedButton11)
<<<<<<< Updated upstream
	ON_BN_CLICKED(IDC_BUTTON12, &CTestDlgDlg::OnBnClickedButton12)
=======
	ON_BN_CLICKED(IDC_BT_SOCKET, &CTestDlgDlg::OnBnClickedBtSocket)
>>>>>>> Stashed changes
END_MESSAGE_MAP()


// CTestDlgDlg message handlers

BOOL CTestDlgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE); //获取系统的menu 即 左上角图标点击的menu
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);  //获取about dialog 的  string
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);  //增加一个分割条
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu); //增加about dialog的menu项 
			//pSysMenu->AppendMenu(MF_BYPOSITION | MF_STRING, SC_MINIMIZE, _T("最小化"));
			//pSysMenu->InsertMenu(2, MF_BYPOSITION|MF_STRING, SC_MINIMIZE, _T("最小化"));
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	//SetTimer(1, 5000, NULL);

	m_pThread = AfxBeginThread(ThreadCheckFunc, this); 

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestDlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	} else if (nID == SC_MINIMIZE){
		ShowWindow(SW_SHOWMINIMIZED);
	} else {
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestDlgDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestDlgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestDlgDlg::OnBnClickedButton1()
{
	DWORD dwStyle = GetStyle();
	dwStyle |= WS_MINIMIZEBOX;
	SetWindowLong(GetSafeHwnd(), GWL_STYLE, dwStyle);
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL) {
		pSysMenu->InsertMenu(2, MF_BYPOSITION|MF_STRING, SC_MINIMIZE, _T("最小化"));
	}
}


void CTestDlgDlg::OnBnClickedButton2()
{
	DWORD dwStyle = GetStyle();
	if (dwStyle & WS_MINIMIZEBOX) {
		dwStyle &= ~WS_MINIMIZEBOX;
		SetWindowLong(GetSafeHwnd(), GWL_STYLE, dwStyle);
		CMenu* pSysMenu = GetSystemMenu(FALSE);
		if (pSysMenu != NULL) {
			pSysMenu->DeleteMenu(2, MF_BYPOSITION);
		}
	}
}


void CTestDlgDlg::OnTimer(UINT_PTR nIDEvent)
{
	CRect rcClient;
	GetClientRect(&rcClient);
	SetWindowPos(NULL, 0, 0, rcClient.Width()+50, rcClient.Height()+100, SWP_NOMOVE);
	//TRACE("hehe\n");
	CDialogEx::OnTimer(nIDEvent);
}


void CTestDlgDlg::OnBnClickedButton3()
{
	CString strPath = _T("g:\\360downloads");

	if (!PathFileExists(strPath)) {
		MessageBox(_T("文件路径不存在"));
		return;
	}
	CFileStatus fileStatus;
 	BOOL bRes = CFile::GetStatus(strPath, fileStatus);
	if (!bRes)
		MessageBox(_T("获取文件属性失败"));
	CFileFind find;
	
	CTime ctime = fileStatus.m_ctime;
	CTime mtime = fileStatus.m_mtime;
	CTime atime = fileStatus.m_atime;

	CString strCTime = ctime.Format(_T("%Y年%m月%d日%H时:%M:%S"));
	CString strMTime = mtime.Format(_T("%Y年%m月%d日%H时:%M:%S"));
	CString strATime = atime.Format(_T("%Y年%m月%d日%H时:%M:%S"));

	CString strName = _T("c?\\ABCD:");

	const int nBufferSize = MAX_PATH;
	TCHAR szBuffer[nBufferSize] = _T("\0");
	DWORD dwRes = GetFullPathName(strName, nBufferSize, szBuffer, NULL);
	if (dwRes == 0) {
		dwRes = GetLastError();
	} else if (dwRes > nBufferSize){
		TCHAR* szlBuffer = new TCHAR[dwRes];
		GetFullPathName(strName, dwRes, szlBuffer, NULL);
		//do something;
		delete szlBuffer;
		szlBuffer = NULL;
	}
}


void CTestDlgDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	TRACE("%d\n", cy);
}


//使用WM_COPYDATA传递消息，另一个进程必须有窗口， 且传递的内容中不能含有带虚函数的类，以及拥有指向自己的指针 cstring
void CTestDlgDlg::OnBnClickedButton4()
{
	UpdateData(TRUE);

	CWnd* pWnd = FindWindow(NULL, _T("PropertyPage"));
	if (pWnd != NULL) {
		COPYDATASTRUCT cds;
		ZeroMemory(&cds, sizeof(cds));
		cds.dwData = 0;
		cds.cbData = (m_string.GetLength() + 1)*2;
		cds.lpData = (LPVOID)(LPCTSTR)m_string;
		pWnd->SendMessage(WM_COPYDATA, (WPARAM)GetSafeHwnd(), (LPARAM)&cds);
	}
}


void CTestDlgDlg::OnBnClickedButton5()
{
	CString strPath = _T("G:\\test\\Adobe Photoshop CS6\\test");
	static int file_num = 0;
	HANDLE hFile;

	DWORD dwBytes=0;
	CString strName;
	strName = strPath;
	strName.AppendFormat(_T("%d"), file_num);
	hFile=CreateFile(strName, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	while (file_num < 100000 && hFile != INVALID_HANDLE_VALUE) 
	{
		WriteFile(hFile, (LPCVOID)(LPCTSTR)strName, (strName.GetLength())*2, &dwBytes, NULL);
		CloseHandle(hFile);
		file_num += 1;
		strName = strPath;
		strName.AppendFormat(_T("%d"), file_num);
		hFile=CreateFile(strName, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	}
	

	CloseHandle(hFile);
}

void CTestDlgDlg::OnBnClickedButton6()
{
	UpdateData(TRUE);
	if (m_string.IsEmpty()) {
		MessageBox(_T("请在文本框中输入内容"));
		return;
	}

	DWORD dwError = 0;
	DWORD dwSize = sizeof(DWORD);
	HANDLE hFile_ = CreateFileMapping((HANDLE)0xFFFFFFFF, NULL, PAGE_READWRITE, 
		0, 50, _T("test file map"));
	if (hFile_ == NULL) {
		dwError = GetLastError();
		CString strError;
		strError.Format(_T("%d"), dwError);

		MessageBox(strError, _T("Error"), MB_OK | MB_ICONERROR);
		return;
	}

	LPVOID lpMap_ = MapViewOfFile(hFile_, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (lpMap_ == NULL) {
		dwError = GetLastError();
		CString strError;
		strError.Format(_T("%d"), dwError);

		MessageBox(strError, _T("Error"), MB_OK | MB_ICONERROR);
		CloseHandle(hFile_);
		return; 
	}

	//TCHAR szName[MAX_PATH] = _T("zhangzhe");
	//memcpy(lpMap_, szName, 50);
	memcpy(lpMap_, (LPCTSTR)m_string, 50);

	UnmapViewOfFile(lpMap_);
	CloseHandle(hFile_);
}


void CTestDlgDlg::OnBnClickedButton8()
{
	DWORD dwSize = 0;   // 0 means message can be any size; 
	DWORD dwError;
	CString strError;
	HANDLE hMailSolt = CreateMailslot(_T("\\\\.\\mailslot\\zhangzhe"), dwSize, 
		MAILSLOT_WAIT_FOREVER, NULL);
	if (hMailSolt == INVALID_HANDLE_VALUE) {
		dwError = GetLastError();
		strError.Format(_T("%d"), dwError);
		MessageBox(strError, _T("error"), MB_ICONERROR);
		return;
	}

	DWORD dwNextSize, dwMessageCount;



	BOOL bRes = GetMailslotInfo(hMailSolt, &dwSize, &dwNextSize, 
		&dwMessageCount, (DWORD)NULL);
	if (!bRes) {
		MessageBox(_T("GetMailslotInfo failed!"));
		CloseHandle(hMailSolt);
	}



	CloseHandle(hMailSolt);
}


void CTestDlgDlg::OnBnClickedButton7()
{
/*
 Test how a critical_section can deadlock
*/
	m_event.SetEvent();
	//m_event.ResetEvent();
}

void CTestDlgDlg::TestCriticalSection()
{
	m_cs.AcquireLock();

	//SendMessage(WM_TEST, 0, 0);

	m_cs.ReleaseLock();
}

LRESULT CTestDlgDlg::OnMsgTest(WPARAM wParam, LPARAM lParam)
{
	TestCriticalSection();
	return 0;
}


void CTestDlgDlg::OnBnClickedButton9()
{
	GetTestApp()->GetSocketThread()->InitSocket();
	GetTestApp()->GetSocketThread()->Startup();
}

//Send Message to InnerWorker
void CTestDlgDlg::OnBnClickedButton10()
{
	// in fact you should move it in OnInitDialog 
	// and only set handler once
	GetTestApp()->SetInnerWorkHandler(new UIHandler(GetSafeHwnd()));
	
	DWORD dwThreadID = GetTestApp()->GetInnerWorkThreadID();
	static TCHAR szText[MAX_PATH] = _T("Hello InnerWorker");
	DWORD dwError = 0;
	BOOL bRes = PostThreadMessage(dwThreadID, WM_THREAD_PRINT, 0, (LPARAM)szText);
	if (!bRes) {
		dwError = GetLastError();
	}
}

LRESULT CTestDlgDlg::OnMessageHandler(WPARAM wParam, LPARAM lParam)
{
	TCHAR* szRes = static_cast<TCHAR*>((LPVOID)lParam);

	MessageBox(szRes);
	return 0;
}

static void PrintMACaddress(unsigned char MACData[])
{
	TRACE("MAC Address: %02X-%02X-%02X-%02X-%02X-%02X\n", 
		MACData[0], MACData[1], MACData[2], MACData[3], MACData[4], MACData[5]);
}

#include <string>

void CTestDlgDlg::OnBnClickedButton11()
{
	int nCharset = GetTextCharset(GetDC()->GetSafeHdc());
	ASSERT(nCharset == GB2312_CHARSET);

	IP_ADAPTER_INFO  AdapterInfo[16];
	DWORD dwBufLen = sizeof(AdapterInfo);
	DWORD dwRet = GetAdaptersInfo(AdapterInfo, &dwBufLen);

	ASSERT(dwRet == ERROR_SUCCESS);

	PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo;
	do {
		pAdapterInfo->AdapterName;
		PrintMACaddress(pAdapterInfo->Address);
		pAdapterInfo = pAdapterInfo->Next;
	} while (pAdapterInfo);
}
<<<<<<< Updated upstream


void CTestDlgDlg::OnBnClickedButton12()
{
	CWnd* pWnd = FindWindow(NULL, _T("UserAccount"));
	if (pWnd != NULL) {
		CWnd* pChild = FindWindowEx(pWnd->GetSafeHwnd(), NULL, NULL, _T("close"));
		
		int nID = pChild->GetDlgCtrlID();
		pWnd->PostMessage(WM_COMMAND, MAKEWPARAM(nID, BN_CLICKED), NULL);
	}
}
=======


void CTestDlgDlg::OnBnClickedBtSocket()
{
	CSocketDlg dlg;
	dlg.DoModal();
}
>>>>>>> Stashed changes
