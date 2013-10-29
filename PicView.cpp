// PicView.cpp : implementation file
//

#include "stdafx.h"
#include "MainProject.h"
#include "PicView.h"
#include "MainProjectDoc.h"
#include "iostream.h"
#include "Data.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPicView

IMPLEMENT_DYNCREATE(CPicView, CView)

CPicView::CPicView()
{
	m_colorPen = RGB(0,0,0);
//	m_colorPenX = RGB(255,255,255);
	m_ptOld=CPoint(0,0);
	m_ptTrace=CPoint(0,0);

	m_PenWidth = 2;
}

CPicView::~CPicView()
{
}


BEGIN_MESSAGE_MAP(CPicView, CView)
	//{{AFX_MSG_MAP(CPicView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPicView drawing

void CPicView::OnDraw(CDC* pDC) // View에서 DC를 얻어다 쓰는것
{
	//CMainProjectDoc* pDoc = GetDocument();  
	// TODO: add draw code here
	for(POSITION pos = m_NodeList.GetHeadPosition(); pos != NULL; ) {
		DrawNode(pDC, (CData *)m_NodeList.GetNext(pos));
	}
	
}

/////////////////////////////////////////////////////////////////////////////
// CPicView diagnostics

#ifdef _DEBUG
void CPicView::AssertValid() const
{
	CView::AssertValid();
}

void CPicView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

#endif //_DEBUG

///////////////////////////////////////////////////////////////////////////////
CMainProjectDoc* CPicView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMainProjectDoc)));
	return (CMainProjectDoc*)m_pDocument;
}
///////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// CPicView message handlers

void CPicView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_ptOld = m_ptTrace = point;
	SetCapture();  // 마우스 메세지가 윈도우 밖에서 발생했을 경우 대비, 
	               // 모든 메세지를 현재 윈도우로 고정시킴
	CView::OnLButtonDown(nFlags, point);
}

void CPicView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	// CMainFrame의 멤버를 쓰기 위한 MainFrame 포인터 얻어오기....
	// 각 포인터들의 좌표를 전해준다....SendingPoint함수에....
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();

	pFrame->SendingPoint(m_SendPoint); // 프레임 뷰의 함수에 데이터 전해준다.

	//////////////////////////////////////////////////////////////////////////
	//
	ReleaseCapture();
	CView::OnLButtonUp(nFlags, point);

}

void CPicView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	if(m_SendPoint.IsEmpty())
		m_SendPoint.RemoveAll(); 

	if ( nFlags & MK_LBUTTON ) {
		CClientDC dc(this); // 그림 그릴때마다 DC를 얻어와야 함....

		// CDC로 DC 얻어 왔을때 Pen만들기
        // CPen : Pen class...

		CPen Pen, *Oldpen;   // Pen 선언
		
		Pen.CreatePen(PS_SOLID, m_PenWidth, m_colorPen);  // Pen 생성
		Oldpen = dc.SelectObject(&Pen);          // 표준 펜 저장

		
		dc.MoveTo(m_ptOld.x, m_ptOld.y);
		dc.LineTo(point.x, point.y);
		m_ptOld = point;
  
		////////////////////////////////////////////////////////////////////////
		// 데이터 저장

		CData *pNode;
		pNode = new CData;
		pNode->m_ptTail = point;
		pNode->m_ptHead = m_ptTrace;
		pNode->m_colorPen = m_colorPen;
		m_NodeList.AddTail(pNode);

		// 보낼 데이터 오브젝트에 Point위치  기억.
		m_SendPoint.AddTail(pNode);
		
		////////////////////////////////////////////////////////////////////////

		m_ptTrace = point;     // 작업이 끝난 후 현재 마우스 커서 위치(Point)를
		                       // 이전 마우스 커서 위치(Trace)로 기억해 둠
		
		dc.SelectObject(Oldpen);                 // 원래 펜 복귀.
		Pen.DeleteObject();                      // 생성한 펜 파괴.
	    
	}
	
	CView::OnMouseMove(nFlags, point);
}

///////////////////////////////////////////////////////////////////
// 
void CPicView::DrawNode(CDC *pDC, CData * pNode)
{
	//AfxMessageBox("s");
	// 노드에 저장된 펜 생성
	CPen pen, *pOldPen;
	if(pNode->m_colorPen > 10)
		m_PenWidth = 10;
	else
		m_PenWidth = 2;

	pen.CreatePen(PS_SOLID, m_PenWidth, pNode->m_colorPen);
	pOldPen = (CPen *)pDC->SelectObject(&pen);

	pDC->MoveTo(pNode->m_ptHead.x, pNode->m_ptHead.y);
	pDC->LineTo(pNode->m_ptTail.x, pNode->m_ptTail.y);

	// DC 복원
	pDC->SelectObject(pOldPen);

}
