#if !defined(AFX_CHATVIEW_H__CDDCBDF6_D7C4_4810_9675_8BF9521D95C0__INCLUDED_)
#define AFX_CHATVIEW_H__CDDCBDF6_D7C4_4810_9675_8BF9521D95C0__INCLUDED_

#include "MainProject.h"
#include "MainProjectDoc.h"
#include "Data.h"
#include "TalkChatCtrl.h"


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChatView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChatView view

class CChatView : public CRichEditView
{
protected:
	CChatView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CChatView)

// Attributes
public:
	CMainProjectDoc* GetDocument();           //Main Document에 연결위한 코드.
	CTalkChatCtrl	 *m_pctrlChat;            // RichEdit 콘트롤 객체
	

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatView)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CChatView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CChatView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////Main Document에 연결위한 코드.
#ifndef _DEBUG  // debug version in MainProjectView.cpp
inline CMainProjectDoc* CChatView::GetDocument()
   { return (CMainProjectDoc*)m_pDocument; }
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATVIEW_H__CDDCBDF6_D7C4_4810_9675_8BF9521D95C0__INCLUDED_)
