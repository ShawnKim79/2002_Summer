// TeditView.cpp : implementation file
//

#include "stdafx.h"
#include "MainProject.h"
// #include "MainProjectDoc.h"
#include "TeditView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTeditView

IMPLEMENT_DYNCREATE(CTeditView, CEditView)

CTeditView::CTeditView()
{
	

}

CTeditView::~CTeditView()
{
}


BEGIN_MESSAGE_MAP(CTeditView, CEditView)
	//{{AFX_MSG_MAP(CTeditView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTeditView drawing

void CTeditView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();

	// TODO: add draw code here

}

/////////////////////////////////////////////////////////////////////////////
// CTeditView diagnostics

#ifdef _DEBUG
void CTeditView::AssertValid() const
{
	CEditView::AssertValid();
}

void CTeditView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////Main Document�� �������� �ڵ�.
CMainProjectDoc* CTeditView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMainProjectDoc)));
	return (CMainProjectDoc*)m_pDocument;
}

// �ᱹ ����� �ϴ� ���ۿ� ����...


void CTeditView::Serialize(CArchive& ar) 
{
	// ���� �д� �κ� 
	//if (ar.IsLoading())
	{
		CFile *pFile = ar.GetFile();
		// ��ī�̺� ����ϸ� �ѹ���Ʈ�� �а� ��....
		int F_Len = pFile->GetLength();
		// ���� ���� ���.

		ASSERT_VALID(this);
		// �������� ��ȿ�� �˻�.(���� ���´�)
		
		LPVOID hText = LocalAlloc(LMEM_MOVEABLE, (F_Len+1)*sizeof(TCHAR));
		// �ؽ�Ʈ �ڵ鿡 ������ ������ ũ�⸸ŭ �޸� �Ҵ�.
		// LMEM_MOVEABLE = �̵��� �޸�,
		// (nLen+1)*sizeof(TCHAR) = �޸� ũ��, TCHAR�� �����ڵ� Ȯ��.

		if (hText == NULL)
			AfxThrowMemoryException();
		// �������� ��� ����ó��
		
		LPTSTR lpszText = (LPTSTR)LocalLock(hText); // �ڵ� ���.
		ASSERT(lpszText != NULL);
		if (ar.Read(lpszText, F_Len*sizeof(TCHAR)) != F_Len*sizeof(TCHAR))
		{
			// ���� �б⿡ �������� ���.
			LocalUnlock(hText); // �ڵ� ����.
			LocalFree(hText);   // �޸� ����.
			AfxThrowArchiveException(CArchiveException::endOfFile);
		}
		// Replace the editing edit buffer with the newly loaded data
		lpszText[F_Len] = '\0';

		// ���� ������ �����쿡 �ѷ��ش�.
		HLOCAL hOldText = GetEditCtrl().GetHandle();
		ASSERT(hOldText != NULL);
		LocalFree(hOldText);
		GetEditCtrl().SetHandle((HLOCAL)(UINT)(DWORD)hText);

		LocalUnlock(hText);
		Invalidate();
		ASSERT_VALID(this);

		this->GetWindowText(m_Txtbuff);

		CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
		pFrame->SendingTxt(&m_Txtbuff);

	}

	//else
	{	// Storing code
	}
}
