#if !defined(AFX_TALKCHATCTRL_H__45F74DD8_4135_44CA_B2C9_894658B80662__INCLUDED_)
#define AFX_TALKCHATCTRL_H__45F74DD8_4135_44CA_B2C9_894658B80662__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TalkChatCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTalkChatCtrl window
// 이 클래스에서는 CChatView에서 만든 CRichEditCtrl을 서브 클래싱 한다.

class CTalkChatCtrl : public CRichEditCtrl
{
// Construction
public:
	CTalkChatCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTalkChatCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTalkChatCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTalkChatCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TALKCHATCTRL_H__45F74DD8_4135_44CA_B2C9_894658B80662__INCLUDED_)
