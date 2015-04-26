#pragma once
class CParseTransfer
{
public:
	CParseTransfer(void);
	~CParseTransfer(void);

	static void InitPath();
	void PraseTransfer(CString& strbuf);

private:
	static CString m_strPath;
	static bool m_bInit;
	CString m_strName;
	CString m_strFile;
};

