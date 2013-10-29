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
	// Ÿ���� ������(��Ʈ��) ����....

	m_pctrlChat = new CTalkChatCtrl;
	// ��Ʈ�� ����...................

	ASSERT_VALID(m_pctrlChat);
	// �޸� �Ҵ� Ȯ��..............

	if(!m_pctrlChat->Create(WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_WANTRETURN | WS_HSCROLL | ES_AUTOHSCROLL | WS_BORDER,
		CRect(0, 0, 0, 0), this, IDC_CHATEDIT))
	{
		TRACE("Failed to Create Chat Control");
		return -1;
	}
	return 0;
}

// CChatView ���� �׸���......
void CChatView::OnSize(UINT nType, int cx, int cy) 
{
	// ���θ��� ��Ʈ�ѵ� ��ġ�� �ٲ��ش�.
	CRichEditView::OnSize(nType, cx, cy);

	CRect rect;
	GetClientRect(rect); // �θ� ���� ũ�� ����.

	if(m_pctrlChat != NULL) m_pctrlChat->MoveWindow(5, rect.Height()-33, cx-10, 30, FALSE);
}

BOOL CChatView::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class

	if (pMsg->message == WM_KEYDOWN){      // �����쿡���� KEY_Down�޼��� �˻�.
		if (pMsg->hwnd == GetSafeHwnd())   // Key_Down�� �Ͼ �������� �ڵ� �˻�.
			                               // ChatView �����쿡�� �޼��� �߻��� 

			
			return TRUE;                   // �޼��� ó�� ����.

	}

	return CRichEditView::PreTranslateMessage(pMsg);
	// PreTranslateMessage(pMsg)���� �޼��� ó���� ���� �͵��� ���ִ�.
	// Ű���� ��ĵ �ڵ带 ó���Ѵ�.
}
