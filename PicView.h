#if !defined(AFX_PICVIEW_H__44824D73_876F_411C_90E2_7847617E9D20__INCLUDED_)
#define AFX_PICVIEW_H__44824D73_876F_411C_90E2_7847617E9D20__INCLUDED_

#include "MainProject.h"
#include "MainProjectDoc.h"
#include "Data.h"
//#include "MainFrm.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PicView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPicView view

class CPicView : public CView
{
protected:
	CPicView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPicView)
		
		// Attributes
public:
	CMainProjectDoc* GetDocument();
	void DrawNode(CDC *, CData *);

	CObList m_SendPoint; // 보내기 위한 데이터 오브젝트	
	CObList m_NodeList;      // 실지 노드 저장.
	
	// Operations
public:
	COLORREF m_colorPen;   // 펜 색
//	COLORREF m_colorPenX;
	CPoint m_ptOld;        // 마우스 눌린지점 좌표
	CPoint m_ptTrace;      // 마우스 이동지점 좌표
	
	int m_PenWidth;


	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPicView)
protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	virtual ~CPicView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CPicView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#ifndef _DEBUG  // debug version in MainProjectView.cpp
inline CMainProjectDoc* CPicView::GetDocument()
   { return (CMainProjectDoc*)m_pDocument; }
#endif



/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICVIEW_H__44824D73_876F_411C_90E2_7847617E9D20__INCLUDED_)
