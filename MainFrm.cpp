// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MainProject.h"
#include "MainProjectDoc.h"
#include "MainFrm.h"

// #include "StartupBox.h"  // Dialog Box Header File

#include "process.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////
// static function(thread function)�� ������� ���� ��ü�� �Ѱ��ֽ� ���� ����ü
typedef struct
{
	CWnd *pWnd;
	SOCKET work;

} THREADPARAM;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_STARTUP, OnStartup)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}
/*
///////////////////////////////////////////////////////////////////////////////
CMainProjectDoc* CMainFrame::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMainProjectDoc)));
	return (CMainProjectDoc*)m_pDocument;
}*/
///////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// ���� ������ ����
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

///////////////////////////////////////////////////////////////////////////////////
// ���� �����ӿ� �޴�, ���¹�, ������ �ٸ� ����
	if (!m_wndPicBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_ALIGN_LEFT
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndPicBar.LoadToolBar(IDR_PicViewToolBar))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndEditBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_ALIGN_RIGHT
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndEditBar.LoadToolBar(IDR_TextToolBar))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

////////////////////////////////////////////////////////////////////////////////////
	
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndPicBar.EnableDocking(CBRS_ALIGN_LEFT);
	m_wndEditBar.EnableDocking(CBRS_ALIGN_RIGHT);

	EnableDocking(CBRS_ALIGN_ANY);

	DockControlBar(&m_wndPicBar);
	DockControlBar(&m_wndEditBar);

	

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
// Ŭ���̾�Ʈ ���� -> ���� ��
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs,
	CCreateContext* pContext)
{   
	if (!m_wndSplitter_1.CreateStatic(this, 2, 1))
	{
		TRACE0("Failed to Create Split bar ");
		return FALSE;
	}   // ���ø� ������ ����� CreateStatic ��� ��� ȣ��

	if (!m_wndSplitter_2.CreateStatic(&m_wndSplitter_1, 1, 2,
		WS_CHILD | WS_VISIBLE, m_wndSplitter_1.IdFromRowCol(0,0)))
	{
		TRACE0("Failed to Create Split bar ");
		return FALSE;
	}   // ���ø� ������ ����� CreateStatic ��� ��� ȣ��

//////////////////////////////////////////////////////////////////////////////
// TODO: adjust the minimum pane size
	m_wndSplitter_2.CreateView(0,0,RUNTIME_CLASS(CPicView),	CSize(500, 200),  
		pContext);

	m_wndSplitter_2.CreateView(0,1, RUNTIME_CLASS(CTeditView),
		CSize(500, 200),      // TODO: adjust the minium pane size
		pContext);

	m_wndSplitter_1.CreateView(1,0, RUNTIME_CLASS(CChatView),
		CSize(500, 400),      // TODO: adjust the minimum pane size
		pContext);

	m_wndSplitter_1.SetRowInfo(0,400,0);
	m_wndSplitter_2.SetColumnInfo(0,400,0);

	return CFrameWnd::OnCreateClient(lpcs,pContext);

////////////////////////////////////////////////////////////////////////////////
// �� �並 ������ �丶�� Ŭ���� ���
}   // ������ ���� ��Ʈ

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnStartup() 
{
	// TODO: Add your command handler code here

	p_View = (CChatView *)m_wndSplitter_1.GetPane(1,0);
	p_PView = (CPicView *)m_wndSplitter_2.GetPane(0,0);
	p_TView = (CTeditView *)m_wndSplitter_2.GetPane(0,1);
	// ��Ƽ�� �� ���� ������ ����...���ø����� �������� �������� GetPane�Լ� �̿�.

	CStartupBox dlg;

	if(dlg.DoModal() == IDOK)
	{
		if(!Work.InitSock()) AfxMessageBox("���� �ʱ�ȭ ����");
			else AfxMessageBox("���� �ʱ�ȭ ����");
			// Socket�� ���� �� �� �� �������� Thread Run		
		
		if(dlg.m_StartSwitch == 0) // ����
		{	
			if(Work.Initialize(7704)) AfxMessageBox("���� ��Ʈ : 7704");
				else AfxMessageBox("���� ��Ʈ ���� ����");
			// ���� ��Ʈ ����

			if(Work.Listen()) AfxMessageBox("���� �۵�");
				else AfxMessageBox("���� �۵� ����");
			// ���� Listen �۾� ����.
			
			AfxBeginThread(CMainFrame::Start_Server, this, 0, 0);
			// ������ ��ŸƮ(���� Proc, ���� Proc�� ����, ������ �켱����, ������ ���� ũ��(�⺻ 1mb))
			
		}
		else if(dlg.m_StartSwitch == 1) // Ŭ���̾�Ʈ
		{
			if(!Work.Connect((LPSTR)(LPCTSTR)dlg.m_strIP, dlg.m_nPortno))
			{
				AfxMessageBox("�������� ����");
				return;
			} 
			AfxMessageBox("�������� ����");	
			
			// ��ü ���� �������� ������ �Լ� ����� �Ұ��ϹǷ�, �����忡 �ְ��� �ϴ� ����
			// (����, ������...)���� ���� �Ѱ��ش�.

			THREADPARAM *param = new THREADPARAM[1];
			param->pWnd = this;
			m_Soc = Work.Get_Socket();

			param->work = m_Soc;

			
			AfxBeginThread(CMainFrame::Start_Client, param, 0, 0);
		}
	}
	
}

//////////////////////////////////////////////////////////////////////////////
// ���� ������
UINT CMainFrame::Start_Server(LPVOID arg)
{
	
	CMainFrame *pFrame = (CMainFrame *)arg;
	CWSASocket* pServerwork = &pFrame->Work;

	THREADPARAM *param = new THREADPARAM[1];
	
	while(1)
	{
		SOCKET work = pServerwork->Accept(); // ���Ʈ �Ǹ� ������ ��ȯ ��
		                                     // �������� ��ſ� ����
	
		if(work == INVALID_SOCKET) continue;

		param->pWnd = pFrame;
		param->work = work;

		pFrame->m_Soc = work;

		AfxBeginThread(CMainFrame::Start_Client, param);
		break;
		// 1:1 ���ῡ�� ���� ������� accept�� �Ǹ� �ӹ��� ����ǹǷ� 
		// Ŭ���̾�Ʈ �Լ��� ������� ������ �ڽ��� ����ȴ�.

	}

	AfxEndThread(0);

	return 0;
}

//////////////////////////////////////////////////////////////////////////////
// Ŭ���̾�Ʈ ������
UINT CMainFrame::Start_Client(LPVOID arg)
{
	DWORD dwReturn;	// �̺�Ʈ�� ����� �߻��ߴ°��� ���� �˻�

	// 
	THREADPARAM *pParam = (THREADPARAM *)arg;
	CMainFrame *pFrame = (CMainFrame *)pParam->pWnd;
	SOCKET Clientwork = pParam->work;

	delete pParam;

	CWSASocket Work;

	CMessage Receive, Send; // ���� �޼����� ���� �޼��� ����

	WSANETWORKEVENTS event; // �̺�Ʈ�� �����ϴ� ��ü
	WSAEVENT hClientRecvEvent = WSACreateEvent(); // �̺�Ʈ �ڵ� ����
	WSAEventSelect(Clientwork, hClientRecvEvent, FD_READ | FD_CLOSE); // ����� �̺�Ʈ ����
	// Socket�� �� ���ŷ ��忡 �ΰ� �̺�Ʈ �߻��� �����쿡 �̺�Ʈ ��ȣ�� ������.

	///////////////////////////////////////////////////////////////////////////////////////////
	// �̺�Ʈ�� ������Ű�� �� �̺�Ʈ�� ���Ͽ� ������Ѽ� ������ �̺�Ʈ�� ���� ����ϵ��� �Ѵ�.
	// �̺�Ʈ�� �߻��Ŀ��� ����, �� �Ŀ� ������ ���Ͽ� ���� ��Ʈ�� �̺�Ʈ�� �˾Ƴ���.
	while(1)
	{
		dwReturn = WSAWaitForMultipleEvents(1, &hClientRecvEvent, FALSE, WSA_INFINITE, FALSE);
		// �̺�Ʈ�� ���.

		if(dwReturn == WSA_WAIT_FAILED)
		{
			int nError = WSAGetLastError();
		} else if(dwReturn == WSA_WAIT_EVENT_0)
		{
			WSAResetEvent(hClientRecvEvent);
		} // �̺�Ʈ ��ȣ ����. -> �̺�Ʈ ��ȣ�� �������־�� �� �̺�Ʈ�� ������ �� �ִ�
		
		WSAEnumNetworkEvents(Clientwork, hClientRecvEvent, &event);

		///////////////////////////////////////////////////////////////////////////////////
		//
		if((event.lNetworkEvents & FD_READ)	== FD_READ) // �б�
		{
			Receive.SetSocket(Clientwork); // Recieve �޼����� ������ ����.... 
			Work.RecvMsg(Clientwork, Receive.Get_DataPtr()); 
			// ���Ͽ��� �޼����� ����(�̺�Ʈ �߻�) Receive �޼����� ����

			pFrame->ProcessMsg(&Receive); // �޼��� ó��.
										  // pFrame�� ����ƽ���� �������� ���� ������ ������.
		}

		if((event.lNetworkEvents & FD_CLOSE) == FD_CLOSE) // �ݱ�
			break;

	}

	WSACloseEvent(hClientRecvEvent);
	
	AfxEndThread(0);
	
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////
// ��뿡�Լ� ���ƿ� �޼����� ó��
void CMainFrame::ProcessMsg(CMessage *pMsg)
{
	char msg_type = pMsg->GetMsgType();

	switch(msg_type)
	{
		// ä��
		case SM_NORMSG:     // ��뿡�Լ� ���� ä�� �޼��� 
			DisplayMsg(pMsg);
			break;

		// �׷���
		case SM_LINE:       // ������
			break;

		case SM_FREELINE:   // ���� ����
			DisplayFline(pMsg);
			break;

		case SM_RACTANGLE:  // �׸�
			break;

		case SM_CIRCLE:     // ��
			break;
		// ��������
		case SM_TEXTTRANS:  // �ؽ�Ʈ ���� ����
			DisplayTxt(pMsg);
			break;
	}
}


/////////////////////////////////////////////////////////////////////////////////////
// �Ϲ� ��ȭ �޼����� Ŭ���̾�Ʈâ�� ǥ��
void CMainFrame::DisplayMsg(CMessage *pMsg)
{
	// �޼������� �ʿ��� �κи� �����ϴ� �۾� �ʿ�!

	CString Msg;

	memcpy((LPSTR)(LPCTSTR)Msg, pMsg->Get_DataPtr()+5, pMsg->Get_DataSize());

	CString Str;
	Str.Format("Client's Talk : %s\r\n", (LPCTSTR)Msg);
	
	p_View->GetRichEditCtrl().SetSel(-1, -1);
	p_View->GetRichEditCtrl().ReplaceSel((LPCTSTR)Str);
	
	p_View->Invalidate();

}

/////////////////////////////////////////////////////////////////////////////////////
// �Ϲ� ��ȭ �޼����� ��뿡�� ����
void CMainFrame::SendingMsg(CString *pS_Msg) // �Ѿ�� ��ü�� �����͸� �޴´�.
{
	CMessage Send;

	Send.Set_Header(SM_NORMSG);  // ��� �¾�
	
	Send.Put_Data((LPSTR)(LPCTSTR)*pS_Msg, pS_Msg->GetLength()+1);
	// 
	Send.CloseMsg();
	Work.SendMsg(m_Soc, Send.Get_DataPtr(), Send.Get_DataSize()+5);
}

//////////////////////////////////////////////////////////////////////
// �� ���� ������ ��� ����....(��� ����)
void CMainFrame::SendingPoint(CObList &point)
{
	BYTE Array[10000]; // �� ���� �����͸� ������ �迭.
	
	// ��� ����
	CData *m_NodeTemp;  // �Ѱ��� ���
	m_NodeTemp = new CData;
	int count=0;

	///////////////////////////////////////////
	// �� ������ ������ ����� �о�� ����(1)
	CPoint m_TempptHead;
	CPoint m_TempptTail;
	COLORREF m_TempcolorPen;
	
	// �� ���� ��� ���� �ȿ� ��ü ����Ʈ�� �ϳ�(Head) ����.
	m_NodeTemp = (CData *)point.GetHead();
	
	POSITION next_Node; // ���� ����� ��ġ ������ ���� 
	
	next_Node = point.GetHeadPosition(); // ���� ����� ��ġ ����
	
	while(next_Node != NULL) // ��尡 ���� ��������.
	{
		// �Ѱ��� ��� �����͸� �о�ͼ� ������ ����� ������ ����(1)�� ����...
		m_TempptHead.x = m_NodeTemp->m_ptHead.x;
		m_TempptHead.y = m_NodeTemp->m_ptHead.y;

		m_TempptTail.x = m_NodeTemp->m_ptTail.x;
		m_TempptTail.y = m_NodeTemp->m_ptTail.y;

		m_TempcolorPen = m_NodeTemp->m_colorPen;
		

		// �� ���� ��ǥ�� ���ۿ� ���� (Byte�� ĳ����)

		*(int *)(Array+count) = m_TempptHead.x;
		count+=4;

		*(int *)(Array+count) = m_TempptHead.y;
		count+=4;
				
		*(int *)(Array+count) = m_TempptTail.x;
		count+=4;
		
		*(int *)(Array+count) = m_TempptTail.y;
		count+=4;
		
		*(int *)(Array+count) = m_TempcolorPen;
		count+=4;		


		// ���� ��� ����.
		m_NodeTemp = (CData *)point.GetNext(next_Node);
	}

	

	// ���� �޼��� ����.
	CMessage Send;
	Send.Set_Header(SM_FREELINE);
	Send.Put_Data(Array, count);
	Send.CloseMsg();
	
	Work.SendMsg(m_Soc, Send.Get_DataPtr(), Send.Get_DataSize()+4);
}

//////////////////////////////////////////////////////////////////////
// �� ���� ������ ��� �޾� ǥ��.....(��� �ռ�)
void CMainFrame::DisplayFline(CMessage *pMsg)
{

	// ����Ǵ� ��� ������
//	CData *m_block;
//	m_block = new CData;
	int count=pMsg->Get_DataSize(); // ��Ŷ ��.
	int i=0; // ��Ŷ ī��Ʈ
	///int checkPen=0;
	//  ���� 
	char *tempMsg = pMsg->Get_DataPtr()+5; // +5�� ��� ����

	while(i < count-5)
	{
		CData *m_block;
		m_block = new CData;

		m_block->m_ptHead.x = *(int *)(tempMsg+i);
		i+=4;

		m_block->m_ptHead.y = *(int *)(tempMsg+i);
		i+=4;
		
		m_block->m_ptTail.x = *(int *)(tempMsg+i);
		i+=4;

		m_block->m_ptTail.y = *(int *)(tempMsg+i);
		i+=4;

		m_block->m_colorPen = *(int *)(tempMsg+i);
	//	if (m_block->m_colorPen > 5) checkPen = 10;
		i+=4;
		
		p_PView->m_NodeList.AddTail(m_block);
	
	}

	//if(checkPen>0) p_PView->m_PenWidth = 10;
		

	p_PView->Invalidate();

}

///////////////////////////////////////////////////////////////////
// Txt File ����
void CMainFrame::SendingTxt(CString *pS_Msg)
{
	CMessage Send;

	Send.Set_Header(SM_TEXTTRANS);  // ��� �¾�
	
	Send.Put_Data((LPSTR)(LPCTSTR)*pS_Msg, pS_Msg->GetLength()+1);
	// 
	Send.CloseMsg();
	Work.SendMsg(m_Soc, Send.Get_DataPtr(), Send.Get_DataSize()+5);

}


///////////////////////////////////////////////////////////////////
// Txt File ǥ��
void CMainFrame::DisplayTxt(CMessage *pMsg)
{
	CString Msg;

	memcpy((LPSTR)(LPCTSTR)Msg, pMsg->Get_DataPtr()+5, pMsg->Get_DataSize());

//	CString Str;
	txtStr.Format((LPCTSTR)Msg);
		
	p_TView->SetWindowText(txtStr);
}