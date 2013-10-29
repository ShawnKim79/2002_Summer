#if !defined(AFX_DATA_H__2B632FCF_65C3_43FB_94A8_5773656F9FC3__INCLUDED_)
#define AFX_DATA_H__2B632FCF_65C3_43FB_94A8_5773656F9FC3__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MainProjectDoc.h"
// Data.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CData command target

class CData : public CObject
{
// Attributes
public:
	CPoint m_ptHead;
	CPoint m_ptTail;
	
	COLORREF m_colorPen;

//////////////////////////////////////////////////////////////////////////////
	virtual void Serialize(CArchive &ar);  
	// Serialize함수는 CObject함수에서 오버라이딩.....
	// 그러므로 가상함수 처리.....
//////////////////////////////////////////////////////////////////////////////

// Operations
public:
	CData();
	virtual ~CData();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CData)
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CData)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATA_H__2B632FCF_65C3_43FB_94A8_5773656F9FC3__INCLUDED_)
