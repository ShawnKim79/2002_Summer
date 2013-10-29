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

void CPicView::OnDraw(CDC* pDC) // View���� DC�� ���� ���°�
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
	SetCapture();  // ���콺 �޼����� ������ �ۿ��� �߻����� ��� ���, 
	               // ��� �޼����� ���� ������� ������Ŵ
	CView::OnLButtonDown(nFlags, point);
}

void CPicView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	// CMainFrame�� ����� ���� ���� MainFrame ������ ������....
	// �� �����͵��� ��ǥ�� �����ش�....SendingPoint�Լ���....
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();

	pFrame->SendingPoint(m_SendPoint); // ������ ���� �Լ��� ������ �����ش�.

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
		CClientDC dc(this); // �׸� �׸������� DC�� ���;� ��....

		// CDC�� DC ��� ������ Pen�����
        // CPen : Pen class...

		CPen Pen, *Oldpen;   // Pen ����
		
		Pen.CreatePen(PS_SOLID, m_PenWidth, m_colorPen);  // Pen ����
		Oldpen = dc.SelectObject(&Pen);          // ǥ�� �� ����

		
		dc.MoveTo(m_ptOld.x, m_ptOld.y);
		dc.LineTo(point.x, point.y);
		m_ptOld = point;
  
		////////////////////////////////////////////////////////////////////////
		// ������ ����

		CData *pNode;
		pNode = new CData;
		pNode->m_ptTail = point;
		pNode->m_ptHead = m_ptTrace;
		pNode->m_colorPen = m_colorPen;
		m_NodeList.AddTail(pNode);

		// ���� ������ ������Ʈ�� Point��ġ  ���.
		m_SendPoint.AddTail(pNode);
		
		////////////////////////////////////////////////////////////////////////

		m_ptTrace = point;     // �۾��� ���� �� ���� ���콺 Ŀ�� ��ġ(Point)��
		                       // ���� ���콺 Ŀ�� ��ġ(Trace)�� ����� ��
		
		dc.SelectObject(Oldpen);                 // ���� �� ����.
		Pen.DeleteObject();                      // ������ �� �ı�.
	    
	}
	
	CView::OnMouseMove(nFlags, point);
}

///////////////////////////////////////////////////////////////////
// 
void CPicView::DrawNode(CDC *pDC, CData * pNode)
{
	//AfxMessageBox("s");
	// ��忡 ����� �� ����
	CPen pen, *pOldPen;
	if(pNode->m_colorPen > 10)
		m_PenWidth = 10;
	else
		m_PenWidth = 2;

	pen.CreatePen(PS_SOLID, m_PenWidth, pNode->m_colorPen);
	pOldPen = (CPen *)pDC->SelectObject(&pen);

	pDC->MoveTo(pNode->m_ptHead.x, pNode->m_ptHead.y);
	pDC->LineTo(pNode->m_ptTail.x, pNode->m_ptTail.y);

	// DC ����
	pDC->SelectObject(pOldPen);

}
