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

/////////////////////////////////////////////////Main Document에 연결위한 코드.
CMainProjectDoc* CTeditView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMainProjectDoc)));
	return (CMainProjectDoc*)m_pDocument;
}

// 결국 여기다 하는 수밖에 없나...


void CTeditView::Serialize(CArchive& ar) 
{
	// 실제 읽는 부분 
	//if (ar.IsLoading())
	{
		CFile *pFile = ar.GetFile();
		// 아카이브 사용하면 한바이트씩 읽게 됨....
		int F_Len = pFile->GetLength();
		// 파일 길이 취득.

		ASSERT_VALID(this);
		// 포인터의 유효성 검사.(자주 나온다)
		
		LPVOID hText = LocalAlloc(LMEM_MOVEABLE, (F_Len+1)*sizeof(TCHAR));
		// 텍스트 핸들에 저장할 파일의 크기만큼 메모리 할당.
		// LMEM_MOVEABLE = 이동성 메모리,
		// (nLen+1)*sizeof(TCHAR) = 메모리 크기, TCHAR는 유니코드 확인.

		if (hText == NULL)
			AfxThrowMemoryException();
		// 실패했을 경우 예외처리
		
		LPTSTR lpszText = (LPTSTR)LocalLock(hText); // 핸들 잠금.
		ASSERT(lpszText != NULL);
		if (ar.Read(lpszText, F_Len*sizeof(TCHAR)) != F_Len*sizeof(TCHAR))
		{
			// 파일 읽기에 실패했을 경우.
			LocalUnlock(hText); // 핸들 해제.
			LocalFree(hText);   // 메모리 해제.
			AfxThrowArchiveException(CArchiveException::endOfFile);
		}
		// Replace the editing edit buffer with the newly loaded data
		lpszText[F_Len] = '\0';

		// 읽은 파일을 윈도우에 뿌려준다.
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
