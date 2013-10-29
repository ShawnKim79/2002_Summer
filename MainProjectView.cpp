// MainProjectView.cpp : implementation of the CMainProjectView class
//

#include "stdafx.h"
#include "MainProject.h"

#include "MainProjectDoc.h"
#include "MainProjectView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainProjectView

IMPLEMENT_DYNCREATE(CMainProjectView, CView)

BEGIN_MESSAGE_MAP(CMainProjectView, CView)
	//{{AFX_MSG_MAP(CMainProjectView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainProjectView construction/destruction

CMainProjectView::CMainProjectView()
{
	// TODO: add construction code here

}

CMainProjectView::~CMainProjectView()
{
}

BOOL CMainProjectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainProjectView drawing

void CMainProjectView::OnDraw(CDC* pDC)
{
	CMainProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMainProjectView printing

BOOL CMainProjectView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMainProjectView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMainProjectView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMainProjectView diagnostics

#ifdef _DEBUG
void CMainProjectView::AssertValid() const
{
	CView::AssertValid();
}

void CMainProjectView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMainProjectDoc* CMainProjectView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMainProjectDoc)));
	return (CMainProjectDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainProjectView message handlers
