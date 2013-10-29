// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__E06D60FE_9873_4518_AF95_6F7772946524__INCLUDED_)
#define AFX_MAINFRM_H__E06D60FE_9873_4518_AF95_6F7772946524__INCLUDED_

#include "WSASocket.h"
#include "StartupBox.h"
#include "Message.h"
#include "Data.h"

// 각 뷰들의 헤더 파일....
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

// Attributes-변수
public:
	CSplitterWnd m_wndSplitter_1;
	CSplitterWnd m_wndSplitter_2;


//	BYTE Array[10000]; // 각 점의 데이터를 저장할 배열.

	CChatView *p_View;  // CChatView를 쓰기 위한 전역 변수.
	CPicView *p_PView;  // CPicView를 쓰기 위한 전역 변수.
	CTeditView *p_TView; // CTeditView를 쓰기 위한 전역 변수.

	CString txtStr; // TXT 파일 저장(내용) 스트링.

// Operations-함수
public:

	////////////////////////////////////////////////////////////////////////
	// 채팅용 함수 모음
	void ProcessMsg(CMessage *pMsg); // 메세지 처리 함수
	void DisplayMsg(CMessage *pMsg); // 받은 채팅 메세지 표시
	void DisplayFline(CMessage *pMsg); // 받은 그래픽 좌표 표시.
	void DisplayTxt(CMessage *pMsg); // 받은 그래픽 좌표 표시.

	void SendingMsg(CString *pS_Msg); // 채팅 메세지 보냄
	void SendingPoint(CObList &point); // 그래픽 좌표 보냄
	void SendingTxt(CString *pS_Msg); // 텍스트 보냄.

	static UINT Start_Server(LPVOID); //객체 생성 없이도 작동.
	static UINT Start_Client(LPVOID);

	SOCKET m_Soc; // 통신에 필요한 포트 넘버를 갖고 있는 소켓.
	
	
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

	// 포트 번호 저장 소켓

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
