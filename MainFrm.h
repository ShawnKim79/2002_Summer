// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__E06D60FE_9873_4518_AF95_6F7772946524__INCLUDED_)
#define AFX_MAINFRM_H__E06D60FE_9873_4518_AF95_6F7772946524__INCLUDED_

#include "WSASocket.h"
#include "StartupBox.h"
#include "Message.h"
#include "Data.h"

// �� ����� ��� ����....
#include "PicView.h"
#include "TeditView.h"
#include "ChatView.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes-����
public:
	CSplitterWnd m_wndSplitter_1;
	CSplitterWnd m_wndSplitter_2;


//	BYTE Array[10000]; // �� ���� �����͸� ������ �迭.

	CChatView *p_View;  // CChatView�� ���� ���� ���� ����.
	CPicView *p_PView;  // CPicView�� ���� ���� ���� ����.
	CTeditView *p_TView; // CTeditView�� ���� ���� ���� ����.

	CString txtStr; // TXT ���� ����(����) ��Ʈ��.

// Operations-�Լ�
public:

	////////////////////////////////////////////////////////////////////////
	// ä�ÿ� �Լ� ����
	void ProcessMsg(CMessage *pMsg); // �޼��� ó�� �Լ�
	void DisplayMsg(CMessage *pMsg); // ���� ä�� �޼��� ǥ��
	void DisplayFline(CMessage *pMsg); // ���� �׷��� ��ǥ ǥ��.
	void DisplayTxt(CMessage *pMsg); // ���� �׷��� ��ǥ ǥ��.

	void SendingMsg(CString *pS_Msg); // ä�� �޼��� ����
	void SendingPoint(CObList &point); // �׷��� ��ǥ ����
	void SendingTxt(CString *pS_Msg); // �ؽ�Ʈ ����.

	static UINT Start_Server(LPVOID); //��ü ���� ���̵� �۵�.
	static UINT Start_Client(LPVOID);

	SOCKET m_Soc; // ��ſ� �ʿ��� ��Ʈ �ѹ��� ���� �ִ� ����.
	
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndPicBar;
	CToolBar    m_wndEditBar;

	// ��Ʈ ��ȣ ���� ����

	CWSASocket Work;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnStartup();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/*
#ifndef _DEBUG  // debug version in MainProjectView.cpp
inline CMainProjectDoc* CMainFrame::GetDocument()
   { return (CMainProjectDoc*)m_pDocument; }
#endif
*/
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__E06D60FE_9873_4518_AF95_6F7772946524__INCLUDED_)
