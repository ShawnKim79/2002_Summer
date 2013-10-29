// TalkChatCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "MainFrm.h"
#include "MainProject.h"
#include "TalkChatCtrl.h"
#include "string.h"
#include "ChatView.h"

// #include "ChatView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTalkChatCtrl

CTalkChatCtrl::CTalkChatCtrl()
{
}

CTalkChatCtrl::~CTalkChatCtrl()
{
}


BEGIN_MESSAGE_MAP(CTalkChatCtrl, CRichEditCtrl)
	//{{AFX_MSG_MAP(CTalkChatCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTalkChatCtrl message handlers
// 메세지 통제......

BOOL CTalkChatCtrl::PreTranslateMessage(MSG* pMsg) 
{
	CString strMyTalk;

	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd(); // 프레임의 SendMsg를 처리하기 위해 포인터를 얻어온다.

	if(pMsg->message == WM_KEYDOWN) // Key Down메세지 발생시
	{
		
		if(pMsg->wParam == VK_RETURN) // 그 키가 Return일 때
		{
			GetWindowText(strMyTalk);

			// Send 함수 호출한다(MainFrame의 포인터를 얻어온 것!)
			pFrame->SendingMsg(&strMyTalk);		// strMyTalk의 객체 포인터를 넘겨준다.
			

			// 부모 윈도우(CChatView)의 포인터 얻어오기.
			CChatView *pView = (CChatView *)GetParent(); 

			SetWindowText("");

			// pView가 상위 윈도우의 포인터를 갖고 있으므로 
			// pView에 직접적으로 코딩하여 작용시킨다.

			strMyTalk += "\r\n";
			
			// CChatView를....strMyTalk로 채움....
			pView->GetRichEditCtrl().SetSel(-1, -1);
			pView->GetRichEditCtrl().ReplaceSel(strMyTalk, FALSE);
			pView->Invalidate();

			return TRUE;              
		}
	}
	
	return CRichEditCtrl::PreTranslateMessage(pMsg);
	
}

//			AfxMessageBox(strMyTalk); // CWnd를 상속 받은 윈도우는 MessageBox를 사용 할수 잇지만
			                          // 그렇지 않은 윈도우는 AfxMessageBox를 사용한다.
