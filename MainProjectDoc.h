// MainProjectDoc.h : interface of the CMainProjectDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINPROJECTDOC_H__EF094BE9_A82E_487F_927C_A3851D296A97__INCLUDED_)
#define AFX_MAINPROJECTDOC_H__EF094BE9_A82E_487F_927C_A3851D296A97__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMainProjectDoc : public CDocument
{
protected: // create from serialization only
	CMainProjectDoc();
	DECLARE_DYNCREATE(CMainProjectDoc)
		
		// Attributes
public:
//	CObList m_List;

	CString m_txtName; // 텍스트 파일 이름.
	int *m_txtBuf;
	
		
	// Operations
public:

	CArchive *m_pAr_txt_in;
	CArchive *m_pAr_txt_out;

	CFile m_txtFilein;
	CFile m_txtFileout;
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainProjectDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

	afx_msg void OnTextfileOpen();
	afx_msg void OnSetPen();
	afx_msg void OnSetErase();

	//}}AFX_VIRTUAL
	
	// Implementation
public:
	virtual ~CMainProjectDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	
protected:
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CMainProjectDoc)

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINPROJECTDOC_H__EF094BE9_A82E_487F_927C_A3851D296A97__INCLUDED_)
