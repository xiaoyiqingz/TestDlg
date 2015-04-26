#include "StdAfx.h"
#include "ParseTransfer.h"

CString CParseTransfer::m_strPath;
bool CParseTransfer::m_bInit = false;

CParseTransfer::CParseTransfer(void)
{
	if (!m_bInit) {
		GetModuleFileName(NULL, m_strPath.GetBuffer(MAX_PATH), MAX_PATH);
		m_strPath.ReleaseBuffer();
		m_strPath = m_strPath.Left(m_strPath.ReverseFind(_T('\\'))+1);
		m_bInit = true;
	}
}


CParseTransfer::~CParseTransfer(void)
{
}

void CParseTransfer::PraseTransfer(CString& strbuf)
{
	int nNameBegin = strbuf.FindOneOf(_T("-name"));
	nNameBegin += 6;
	int nNameEnd = strbuf.Find(_T(' '));
	m_strName = strbuf.Mid(nNameBegin , nNameEnd-nNameBegin);

	int nFileBegin = strbuf.Find(_T("-file"));
	nFileBegin +=6;
	m_strFile = strbuf.Mid(nFileBegin, strbuf.GetLength()-nFileBegin);

	m_strPath += m_strName;
	HANDLE hFile = CreateFile(m_strPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 
		FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		ASSERT(0);
	}
	
	DWORD dwWrited;
	WriteFile(hFile, (LPVOID)m_strFile.GetBuffer(), m_strFile.GetLength()*2, 
		&dwWrited, NULL);
	if (dwWrited != m_strFile.GetLength()*2) {
		ASSERT(0);
	}

	CloseHandle(hFile);
}
