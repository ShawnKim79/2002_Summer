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
// �޼��� ����......

BOOL CTalkChatCtrl::PreTranslateMessage(MSG* pMsg) 
{
	CString strMyTalk;

	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd(); // �������� SendMsg�� ó���ϱ� ���� �����͸� ���´�.

	if(pMsg->message == WM_KEYDOWN) // Key Down�޼��� �߻���
	{
		
		if(pMsg->wParam == VK_RETURN) // �� Ű�� Return�� ��
		{
			GetWindowText(strMyTalk);

			// Send �Լ� ȣ���Ѵ�(MainFrame�� �����͸� ���� ��!)
			pFrame->SendingMsg(&strMyTalk);		// strMyTalk�� ��ü �����͸� �Ѱ��ش�.
			

			// �θ� ������(CChatView)�� ������ ������.
			CChatView *pView = (CChatView *)GetParent(); 

			SetWindowText("");

			// pView�� ���� �������� �����͸� ���� �����Ƿ� 
			// pView�� ���������� �ڵ��Ͽ� �ۿ��Ų��.

			strMyTalk += "\r\n";
			
			// CChatView��....strMyTalk�� ä��....
			pView->GetRichEditCtrl().SetSel(-1, -1);
			pView->GetRichEditCtrl().ReplaceSel(strMyTalk, FALSE);
			pView->Invalidate();

			return TRUE;              
		}
	}
	
	return CRichEditCtrl::PreTranslateMessage(pMsg);
	
}

//			AfxMessageBox(strMyTalk); // CWnd�� ��� ���� ������� MessageBox�� ��� �Ҽ� ������
			                          // �׷��� ���� ������� AfxMessageBox�� ����Ѵ�.
