#pragma once


// CSocketDlg dialog

class CSocketDlg : public CDialog
{
	DECLARE_DYNAMIC(CSocketDlg)
private:
	SOCKET	m_socket; 
	CString m_strSend;
public:
	CSocketDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSocketDlg();

// Dialog Data
	enum { IDD = IDD_SOCKETDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtSend();
	afx_msg void OnBnClickedBtInit();
};
