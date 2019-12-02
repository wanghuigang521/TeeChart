// MSCommTestDlg.h : header file
//
//{{AFX_INCLUDES()
#include "mscomm.h"
//}}AFX_INCLUDES


#if !defined(AFX_MSCOMMTESTDLG_H__7FEAE52E_D815_4208_8B88_F97AE4A6905B__INCLUDED_)
#define AFX_MSCOMMTESTDLG_H__7FEAE52E_D815_4208_8B88_F97AE4A6905B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMSCommTestDlg dialog

class CMSCommTestDlg : public CDialog
{
// Construction
public:
	CMSCommTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMSCommTestDlg)
	enum { IDD = IDD_MSCOMMTEST_DIALOG };
	CString	m_strEditRXData;
	CString	m_strEditTXData;
	CMSComm	m_ctrlComm;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMSCommTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMSCommTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnComm();
	afx_msg void OnButtonManualsend();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEditTxdata();
	afx_msg void OnCbnSelchangeCombo1();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSCOMMTESTDLG_H__7FEAE52E_D815_4208_8B88_F97AE4A6905B__INCLUDED_)
