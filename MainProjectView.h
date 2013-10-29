// MainProjectView.h : interface of the CMainProjectView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINPROJECTVIEW_H__FA743C2E_F21C_4480_B452_E80ACFA6A847__INCLUDED_)
#define AFX_MAINPROJECTVIEW_H__FA743C2E_F21C_4480_B452_E80ACFA6A847__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// 이 클래스는 필요가 업ㅂ을 수도 있다
class CMainProjectView : public CView
{
protected: // create from serialization only
	CMainProjectView();
	DECLARE_DYNCREATE(CMainProjectView)

// Attributes
public:
	CMainProjectDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainProjectView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainProjectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMainProjectView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MainProjectView.cpp
inline CMainProjectDoc* CMainProjectView::GetDocument()
   { return (CMainProjectDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINPROJECTVIEW_H__FA743C2E_F21C_4480_B452_E80ACFA6A847__INCLUDED_)
