#if !defined(AFX_STARTUPBOX_H__EE0EB801_E32C_414A_875B_A2A48537D28B__INCLUDED_)
#define AFX_STARTUPBOX_H__EE0EB801_E32C_414A_875B_A2A48537D28B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StartupBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStartupBox dialog

class CStartupBox : public CDialog
{
// Construction
public:
	CStartupBox(CWnd* pParent = NULL);   // standard constructor
	int m_nPortno;
	CString m_strIP;

// Dialog Data
	//{{AFX_DATA(CStartupBox)
	enum { IDD = IDD_STARTUP_DIALOG };
	int		m_StartSwitch;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStartupBox)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStartupBox)
	afx_msg void OnRadioserver();
	afx_msg void OnOk();
	afx_msg void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};




//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STARTUPBOX_H__EE0EB801_E32C_414A_875B_A2A48537D28B__INCLUDED_)
