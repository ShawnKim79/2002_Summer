// MainProjectDoc.cpp : implementation of the CMainProjectDoc class
//

#include "stdafx.h"
#include "MainProject.h"
#include "Data.h"
#include "MainProjectDoc.h"
#include "TeditView.h"
#include "PicView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainProjectDoc

IMPLEMENT_DYNCREATE(CMainProjectDoc, CDocument)

BEGIN_MESSAGE_MAP(CMainProjectDoc, CDocument)
	//{{AFX_MSG_MAP(CMainProjectDoc)
	ON_COMMAND(ID_TEXTFILE_OPEN, OnTextfileOpen)
	ON_COMMAND(ID_BUTTON_BLACKPEN, OnSetPen)
	ON_COMMAND(ID_BUTTON_ERASE, OnSetErase)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainProjectDoc construction/destruction

CMainProjectDoc::CMainProjectDoc()
{
	// TODO: add one-time construction code here
	m_pAr_txt_in = new CArchive(&m_txtFilein, CArchive::load );
	m_pAr_txt_out = new CArchive(&m_txtFileout, CArchive::store );
	// 파일과 아카이브 연결

}

CMainProjectDoc::~CMainProjectDoc()
{
}

BOOL CMainProjectDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMainProjectDoc serialization  // 현재는 CPicView의 데이터를 저장함...(바꿔야 겠지)

void CMainProjectDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}

}

/////////////////////////////////////////////////////////////////////////////
// CMainProjectDoc diagnostics

#ifdef _DEBUG
void CMainProjectDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMainProjectDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


void CMainProjectDoc::OnTextfileOpen() 
{
	// TODO: Add your command handler code here
	// 파일 Read Part.
	// 순서 : 다이얼로그로 파일 패스 읽음
	//      -> CFile로 오픈
	//      -> Read / Write 기능 구현(View 타겟도 정해준다.)
	//      -> 끝

	CFileDialog	m_Text
 		( TRUE, "TXT", NULL, OFN_HIDEREADONLY | OFN_ENABLESIZING,
		"Text Files(*.txt)|*.txt|(All Files(*.*)|*.*||" , NULL);  
	// m_Text : 읽어올 파일을 다이얼로그 윈도우에서 읽어 저장할 객체.

	if(m_Text.DoModal() == IDOK)
	{
		m_txtName = m_Text.GetPathName();
		// 파일 경로 저장.
		m_txtFilein.Open(m_txtName, CFile::modeRead, NULL);
		// 파일 오픈(File Path, nFlag(읽기), NULL)
		// m_txtFilein : CFile 형 변수......

		CMainFrame *pFrame = (CMainFrame *) AfxGetMainWnd(); 
		// 메인 윈도우 프레임 포인터 얻고서 (스플릿은 프레임에 종속.....)
		CTeditView *pTView = (CTeditView *) pFrame->m_wndSplitter_2.GetPane(0, 1); 
		// 액티브 된 뷰의 포인터 얻어기...스플릿으로 나누어져 있을때는 GetPane함수 이용

		pTView->Serialize(*m_pAr_txt_in); 
		// Serialize로 파일 연결

	}// 파일 다이얼로그 박스 열어 파일 읽음.
}

void CMainProjectDoc::OnSetPen()
{
	CPicView *pView = (CPicView *)((CMainFrame *)AfxGetMainWnd())->GetActiveView();
    pView->m_colorPen = RGB(0,0,0);
	pView->m_PenWidth = 2;
	
}

void CMainProjectDoc::OnSetErase()
{
	CPicView *pView = (CPicView *)((CMainFrame *)AfxGetMainWnd())->GetActiveView();
    pView->m_colorPen = RGB(255,255,255);
	pView->m_PenWidth = 10;

}