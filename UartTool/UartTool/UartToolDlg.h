
// UartToolDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "commscomm.h"


// CUartToolDlg dialog
class CUartToolDlg : public CDialogEx
{
// Construction
public:
	CUartToolDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_UARTTOOL_DIALOG };

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
	DECLARE_MESSAGE_MAP()
private:
	CString m_EditRxData;
	CString m_EditTxData;
	CComboBox m_ComboPortNumber;
	CComboBox m_ComboBaud;
	CButton m_BtnOpen;
	CButton m_BtnClose;
	CButton m_BtnSend;
	CButton m_BtnClear;
	CCommscomm m_ComMscomm;
	CButton m_ChkTimeStamp;
public:
	afx_msg void OnBnClickedBtnopen();
	afx_msg void OnBnClickedBtnclose();
	afx_msg void OnBnClickedBtnsend();
	DECLARE_EVENTSINK_MAP()
	void OnCommCommscomm();
	afx_msg void OnBnClickedBtnclear();
	afx_msg void OnBnClickedBtnQuit();
};
