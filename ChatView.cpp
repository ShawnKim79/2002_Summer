// ChatView.cpp : implementation file
//

#include "stdafx.h"
#include "MainProject.h"
#include "ChatView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChatView

IMPLEMENT_DYNCREATE(CChatView, CRichEditView)

CChatView::CChatView()
{
	m_pctrlChat = NULL;
}

CChatView::~CChatView()
{
}


BEGIN_MESSAGE_MAP(CChatView, CRichEditView)
	//{{AFX_MSG_MAP(CChatView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatView drawing

void CChatView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CChatView diagnostics

#ifdef _DEBUG
void CChatView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CChatView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}
#endif //_DEBUG


///////////////////////////////////////////////////////////////////////////////
CMainProjectDoc* CChatView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMainProjectDoc)));
	return (CMainProjectDoc*)m_pDocument;
}
///////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CChatView message handlers




int CChatView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CRichEditView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	// 타이핑 윈도우(컨트롤) 생성....

	m_pctrlChat = new CTalkChatCtrl;
	// 콘트롤 생성...................

	ASSERT_VALID(m_pctrlChat);
	// 메모리 할당 확인..............

	if(!m_pctrlChat->Create(WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_WANTRETURN | WS_HSCROLL | ES_AUTOHSCROLL | WS_BORDER,
		CRect(0, 0, 0, 0), this, IDC_CHATEDIT))
	{
		TRACE("Failed to Create Chat Control");
		return -1;
	}
	return 0;
}

// CChatView 새로 그릴때......
void CChatView::OnSize(UINT nType, int cx, int cy) 
{
	// 새로만든 컨트롤도 위치를 바꿔준다.
	CRichEditView::OnSize(nType, cx, cy);

	CRect rect;
	GetClientRect(rect); // 부모 뷰의 크기 받음.

	if(m_pctrlChat != NULL) m_pctrlChat->MoveWindow(5, rect.Height()-33, cx-10, 30, FALSE);
}

BOOL CChatView::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class

	if (pMsg->message == WM_KEYDOWN){      // 윈도우에서의 KEY_Down메세지 검색.
		if (pMsg->hwnd == GetSafeHwnd())   // Key_Down이 일어난 윈도우의 핸들 검색.
			                               // ChatView 윈도우에서 메세지 발생시 

			
			return TRUE;                   // 메세지 처리 안함.

	}

	return CRichEditView::PreTranslateMessage(pMsg);
	// PreTranslateMessage(pMsg)에는 메세지 처리를 위한 것들이 모여있다.
	// 키보드 스캔 코드를 처리한다.
}
