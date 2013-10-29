// MainProject.h : main header file for the MAINPROJECT application
//

#if !defined(AFX_MAINPROJECT_H__70615417_EEC8_4496_8160_53253A55A1A5__INCLUDED_)
#define AFX_MAINPROJECT_H__70615417_EEC8_4496_8160_53253A55A1A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMainProjectApp:
// See MainProject.cpp for the implementation of this class
//

class CMainProjectApp : public CWinApp
{
public:
	CMainProjectApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainProjectApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMainProjectApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINPROJECT_H__70615417_EEC8_4496_8160_53253A55A1A5__INCLUDED_)
