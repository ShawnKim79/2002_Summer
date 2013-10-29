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
	// ���ϰ� ��ī�̺� ����

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
// CMainProjectDoc serialization  // ����� CPicView�� �����͸� ������...(�ٲ�� ����)

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
	// ���� Read Part.
	// ���� : ���̾�α׷� ���� �н� ����
	//      -> CFile�� ����
	//      -> Read / Write ��� ����(View Ÿ�ٵ� �����ش�.)
	//      -> ��

	CFileDialog	m_Text
 		( TRUE, "TXT", NULL, OFN_HIDEREADONLY | OFN_ENABLESIZING,
		"Text Files(*.txt)|*.txt|(All Files(*.*)|*.*||" , NULL);  
	// m_Text : �о�� ������ ���̾�α� �����쿡�� �о� ������ ��ü.

	if(m_Text.DoModal() == IDOK)
	{
		m_txtName = m_Text.GetPathName();
		// ���� ��� ����.
		m_txtFilein.Open(m_txtName, CFile::modeRead, NULL);
		// ���� ����(File Path, nFlag(�б�), NULL)
		// m_txtFilein : CFile �� ����......

		CMainFrame *pFrame = (CMainFrame *) AfxGetMainWnd(); 
		// ���� ������ ������ ������ ��� (���ø��� �����ӿ� ����.....)
		CTeditView *pTView = (CTeditView *) pFrame->m_wndSplitter_2.GetPane(0, 1); 
		// ��Ƽ�� �� ���� ������ ����...���ø����� �������� �������� GetPane�Լ� �̿�

		pTView->Serialize(*m_pAr_txt_in); 
		// Serialize�� ���� ����

	}// ���� ���̾�α� �ڽ� ���� ���� ����.
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