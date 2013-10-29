#if !defined(AFX_TEDITVIEW_H__1368EFFA_9F86_4701_BD42_F2E7622F1DE0__INCLUDED_)
#define AFX_TEDITVIEW_H__1368EFFA_9F86_4701_BD42_F2E7622F1DE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TeditView.h : header file
//

#include "MainProjectDoc.h"         //Main Document에 연결위한 코드.

/////////////////////////////////////////////////////////////////////////////
// CTeditView view - TEXT 출력 및 편집.

class CTeditView : public CEditView
{
protected:
	CTeditView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CTeditView)

// Attributes
public:
	CMainProjectDoc* GetDocument();           //Main Document에 연결위한 코드.

	CString m_Txtbuff;
	

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTeditView)
	public:
	virtual void Serialize(CArchive& ar);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTeditView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CTeditView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////Main Document에 연결위한 코드.
#ifndef _DEBUG  // debug version in MainProjectView.cpp
inline CMainProjectDoc* CTeditView::GetDocument()
   { return (CMainProjectDoc*)m_pDocument; }
#endif


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEDITVIEW_H__1368EFFA_9F86_4701_BD42_F2E7622F1DE0__INCLUDED_)
