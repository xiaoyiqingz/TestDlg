
// TestDlgDlg.h : header file
//

#pragma once
#include "Help/MyCrtitcal.h"

/*
CEvent(
	BOOL bInitiallyOwn = FALSE,
	BOOL bManualReset = FALSE,
	LPCTSTR lpszName = NULL,
	LPSECURITY_ATTRIBUTES lpsaAttribute = NULL 
	);
bInitiallyOwn:ָ���¼������ʼ��״̬��TRUEΪ���źţ�FALSEΪ���źţ�
bManualReset��ָ��Ҫ�������¼��������˹��¼������Զ��¼���TRUEΪ�˹��¼���FALSEΪ�Զ��¼���
*/

// CTestDlgDlg dialog
class CTestDlgDlg : public CDialogEx
{
private:
	CMyCritical  m_cs;
	CEvent		m_event;
	CWinThread* m_pThread;

public:
	CString m_string;

// Construction
public:
	CTestDlgDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TESTDLG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	static UINT AFX_CDECL ThreadCheckFunc(LPVOID pParam);
	void TestCriticalSection();


	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton3();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton7();
	afx_msg LRESULT OnMsgTest(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg LRESULT OnMessageHandler(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedBtSocket();
};
