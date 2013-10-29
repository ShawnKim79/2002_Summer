#if !defined(AFX_CHATTALK_H__44E6A2B0_5BA3_415F_8E2D_526A1A67D755__INCLUDED_)
#define AFX_CHATTALK_H__44E6A2B0_5BA3_415F_8E2D_526A1A67D755__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChatTalk.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChatTalk window

class CChatTalk : public CRichEditCtrl
{
// Construction
public:
	CChatTalk();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatTalk)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChatTalk();

	// Generated message map functions
protected:
	//{{AFX_MSG(CChatTalk)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATTALK_H__44E6A2B0_5BA3_415F_8E2D_526A1A67D755__INCLUDED_)
