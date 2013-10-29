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
// static function(thread function)에 윈도우와 소켓 객체를 넘겨주시 위한 구조체
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
// 메인 프레임 생성
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

///////////////////////////////////////////////////////////////////////////////////
// 메인 프레임에 메뉴, 상태바, 아이콘 바를 생성
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
// 클라이언트 생성 -> 분할 뷰
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs,
	CCreateContext* pContext)
{   
	if (!m_wndSplitter_1.CreateStatic(this, 2, 1))
	{
		TRACE0("Failed to Create Split bar ");
		return FALSE;
	}   // 스플릿 윈도우 만들고 CreateStatic 멤버 펑션 호출

	if (!m_wndSplitter_2.CreateStatic(&m_wndSplitter_1, 1, 2,
		WS_CHILD | WS_VISIBLE, m_wndSplitter_1.IdFromRowCol(0,0)))
	{
		TRACE0("Failed to Create Split bar ");
		return FALSE;
	}   // 스플릿 윈도우 만들고 CreateStatic 멤버 펑션 호출

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
// 각 뷰를 나누고 뷰마다 클래스 등록
}   // 윈도우 분할 파트

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
	// 액티브 된 뷰의 포인터 얻어기...스플릿으로 나누어져 있을때는 GetPane함수 이용.

	CStartupBox dlg;

	if(dlg.DoModal() == IDOK)
	{
		if(!Work.InitSock()) AfxMessageBox("소켓 초기화 실패");
			else AfxMessageBox("소켓 초기화 성공");
			// Socket을 생성 한 후 그 소켓으로 Thread Run		
		
		if(dlg.m_StartSwitch == 0) // 서버
		{	
			if(Work.Initialize(7704)) AfxMessageBox("서버 포트 : 7704");
				else AfxMessageBox("서버 포트 오픈 실패");
			// 서버 포트 오픈

			if(Work.Listen()) AfxMessageBox("서버 작동");
				else AfxMessageBox("서버 작동 실패");
			// 서버 Listen 작업 시작.
			
			AfxBeginThread(CMainFrame::Start_Server, this, 0, 0);
			// 스레드 스타트(실행 Proc, 실행 Proc의 인자, 스레드 우선순위, 스레드 스택 크기(기본 1mb))
			
		}
		else if(dlg.m_StartSwitch == 1) // 클라이언트
		{
			if(!Work.Connect((LPSTR)(LPCTSTR)dlg.m_strIP, dlg.m_nPortno))
			{
				AfxMessageBox("서버연결 실패");
				return;
			} 
			AfxMessageBox("서버연결 성공");	
			
			// 객체 생성 이전에는 스레드 함수 사용이 불가하므로, 스레드에 주고자 하는 인자
			// (소켓, 윈도우...)들을 묶어 넘겨준다.

			THREADPARAM *param = new THREADPARAM[1];
			param->pWnd = this;
			m_Soc = Work.Get_Socket();

			param->work = m_Soc;

			
			AfxBeginThread(CMainFrame::Start_Client, param, 0, 0);
		}
	}
	
}

//////////////////////////////////////////////////////////////////////////////
// 서버 스레드
UINT CMainFrame::Start_Server(LPVOID arg)
{
	
	CMainFrame *pFrame = (CMainFrame *)arg;
	CWSASocket* pServerwork = &pFrame->Work;

	THREADPARAM *param = new THREADPARAM[1];
	
	while(1)
	{
		SOCKET work = pServerwork->Accept(); // 어셉트 되면 소켓이 반환 됨
		                                     // 실질적인 통신용 소켓
	
		if(work == INVALID_SOCKET) continue;

		param->pWnd = pFrame;
		param->work = work;

		pFrame->m_Soc = work;

		AfxBeginThread(CMainFrame::Start_Client, param);
		break;
		// 1:1 연결에서 서버 스레드는 accept가 되면 임무가 종료되므로 
		// 클라이언트 함수를 스레드로 돌리고 자신은 종료된다.

	}

	AfxEndThread(0);

	return 0;
}

//////////////////////////////////////////////////////////////////////////////
// 클라이언트 스레드
UINT CMainFrame::Start_Client(LPVOID arg)
{
	DWORD dwReturn;	// 이벤트가 제대로 발생했는가에 대한 검사

	// 
	THREADPARAM *pParam = (THREADPARAM *)arg;
	CMainFrame *pFrame = (CMainFrame *)pParam->pWnd;
	SOCKET Clientwork = pParam->work;

	delete pParam;

	CWSASocket Work;

	CMessage Receive, Send; // 보낼 메세지와 받을 메세지 생성

	WSANETWORKEVENTS event; // 이벤트를 저장하는 객체
	WSAEVENT hClientRecvEvent = WSACreateEvent(); // 이벤트 핸들 생성
	WSAEventSelect(Clientwork, hClientRecvEvent, FD_READ | FD_CLOSE); // 사용할 이벤트 고르기
	// Socket을 비 블로킹 모드에 두고 이벤트 발생시 윈도우에 이벤트 신호를 보낸다.

	///////////////////////////////////////////////////////////////////////////////////////////
	// 이벤트를 생성시키고 그 이벤트를 소켓에 연결시켜서 소켓이 이벤트에 대해 대기하도록 한다.
	// 이벤트는 발생후에는 리셋, 그 후에 지정된 소켓에 대한 네트웍 이벤트를 알아낸다.
	while(1)
	{
		dwReturn = WSAWaitForMultipleEvents(1, &hClientRecvEvent, FALSE, WSA_INFINITE, FALSE);
		// 이벤트의 대기.

		if(dwReturn == WSA_WAIT_FAILED)
		{
			int nError = WSAGetLastError();
		} else if(dwReturn == WSA_WAIT_EVENT_0)
		{
			WSAResetEvent(hClientRecvEvent);
		} // 이벤트 신호 리셋. -> 이벤트 신호를 리셋해주어야 새 이벤트를 적용할 수 있다
		
		WSAEnumNetworkEvents(Clientwork, hClientRecvEvent, &event);

		///////////////////////////////////////////////////////////////////////////////////
		//
		if((event.lNetworkEvents & FD_READ)	== FD_READ) // 읽기
		{
			Receive.SetSocket(Clientwork); // Recieve 메세지와 소켓을 연결.... 
			Work.RecvMsg(Clientwork, Receive.Get_DataPtr()); 
			// 소켓에서 메세지가 오면(이벤트 발생) Receive 메세지에 저장

			pFrame->ProcessMsg(&Receive); // 메세지 처리.
										  // pFrame은 스태틱에서 쓰기위해 얻어온 윈도우 포인터.
		}

		if((event.lNetworkEvents & FD_CLOSE) == FD_CLOSE) // 닫기
			break;

	}

	WSACloseEvent(hClientRecvEvent);
	
	AfxEndThread(0);
	
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////
// 상대에게서 날아온 메세지를 처리
void CMainFrame::ProcessMsg(CMessage *pMsg)
{
	char msg_type = pMsg->GetMsgType();

	switch(msg_type)
	{
		// 채팅
		case SM_NORMSG:     // 상대에게서 받은 채팅 메세지 
			DisplayMsg(pMsg);
			break;

		// 그래픽
		case SM_LINE:       // 일직선
			break;

		case SM_FREELINE:   // 프리 라인
			DisplayFline(pMsg);
			break;

		case SM_RACTANGLE:  // 네모
			break;

		case SM_CIRCLE:     // 원
			break;
		// 파일전송
		case SM_TEXTTRANS:  // 텍스트 파일 전송
			DisplayTxt(pMsg);
			break;
	}
}


/////////////////////////////////////////////////////////////////////////////////////
// 일반 대화 메세지를 클라이언트창에 표시
void CMainFrame::DisplayMsg(CMessage *pMsg)
{
	// 메세지에서 필요한 부분만 추출하는 작업 필요!

	CString Msg;

	memcpy((LPSTR)(LPCTSTR)Msg, pMsg->Get_DataPtr()+5, pMsg->Get_DataSize());

	CString Str;
	Str.Format("Client's Talk : %s\r\n", (LPCTSTR)Msg);
	
	p_View->GetRichEditCtrl().SetSel(-1, -1);
	p_View->GetRichEditCtrl().ReplaceSel((LPCTSTR)Str);
	
	p_View->Invalidate();

}

/////////////////////////////////////////////////////////////////////////////////////
// 일반 대화 메세지를 상대에게 전송
void CMainFrame::SendingMsg(CString *pS_Msg) // 넘어온 객체의 포인터를 받는다.
{
	CMessage Send;

	Send.Set_Header(SM_NORMSG);  // 헤더 셋업
	
	Send.Put_Data((LPSTR)(LPCTSTR)*pS_Msg, pS_Msg->GetLength()+1);
	// 
	Send.CloseMsg();
	Work.SendMsg(m_Soc, Send.Get_DataPtr(), Send.Get_DataSize()+5);
}

//////////////////////////////////////////////////////////////////////
// 각 점의 데이터 노드 보냄....(노드 분해)
void CMainFrame::SendingPoint(CObList &point)
{
	BYTE Array[10000]; // 각 점의 데이터를 저장할 배열.
	
	// 노드 조작
	CData *m_NodeTemp;  // 한개의 노드
	m_NodeTemp = new CData;
	int count=0;

	///////////////////////////////////////////
	// 한 노드안의 데이터 멤버를 읽어올 변수(1)
	CPoint m_TempptHead;
	CPoint m_TempptTail;
	COLORREF m_TempcolorPen;
	
	// 한 개의 노드 구조 안에 전체 리스트중 하나(Head) 저장.
	m_NodeTemp = (CData *)point.GetHead();
	
	POSITION next_Node; // 현재 노드의 위치 저장할 변수 
	
	next_Node = point.GetHeadPosition(); // 현재 노드의 위치 저장
	
	while(next_Node != NULL) // 노드가 끝이 날때까지.
	{
		// 한개의 노드 데이터를 읽어와서 데이터 멤버를 저장할 변수(1)에 자장...
		m_TempptHead.x = m_NodeTemp->m_ptHead.x;
		m_TempptHead.y = m_NodeTemp->m_ptHead.y;

		m_TempptTail.x = m_NodeTemp->m_ptTail.x;
		m_TempptTail.y = m_NodeTemp->m_ptTail.y;

		m_TempcolorPen = m_NodeTemp->m_colorPen;
		

		// 각 점의 좌표를 버퍼에 저장 (Byte로 캐스팅)

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


		// 다음 노드 지정.
		m_NodeTemp = (CData *)point.GetNext(next_Node);
	}

	

	// 실제 메세지 생성.
	CMessage Send;
	Send.Set_Header(SM_FREELINE);
	Send.Put_Data(Array, count);
	Send.CloseMsg();
	
	Work.SendMsg(m_Soc, Send.Get_DataPtr(), Send.Get_DataSize()+4);
}

//////////////////////////////////////////////////////////////////////
// 각 점의 데이터 노드 받아 표시.....(노드 합성)
void CMainFrame::DisplayFline(CMessage *pMsg)
{

	// 저장되는 노드 데이터
//	CData *m_block;
//	m_block = new CData;
	int count=pMsg->Get_DataSize(); // 패킷 량.
	int i=0; // 패킷 카운트
	///int checkPen=0;
	//  서버 
	char *tempMsg = pMsg->Get_DataPtr()+5; // +5는 헤더 제거

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
// Txt File 전송
void CMainFrame::SendingTxt(CString *pS_Msg)
{
	CMessage Send;

	Send.Set_Header(SM_TEXTTRANS);  // 헤더 셋업
	
	Send.Put_Data((LPSTR)(LPCTSTR)*pS_Msg, pS_Msg->GetLength()+1);
	// 
	Send.CloseMsg();
	Work.SendMsg(m_Soc, Send.Get_DataPtr(), Send.Get_DataSize()+5);

}


///////////////////////////////////////////////////////////////////
// Txt File 표시
void CMainFrame::DisplayTxt(CMessage *pMsg)
{
	CString Msg;

	memcpy((LPSTR)(LPCTSTR)Msg, pMsg->Get_DataPtr()+5, pMsg->Get_DataSize());

//	CString Str;
	txtStr.Format((LPCTSTR)Msg);
		
	p_TView->SetWindowText(txtStr);
}