// WSASocket.cpp: implementation of the CWSASocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MainProject.h"
#include "WSASocket.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWSASocket::CWSASocket()
{

}

CWSASocket::~CWSASocket()
{

}


///////////////////////////////////////////////////////////////////////////////////////////////////
//
SOCKET CWSASocket::Accept()
{
	SOCKET ListenSocket;          // ListenSocket ����

	struct sockaddr_in sa;        // ���� ���� ����
	int Length;

	ZeroMemory(&sa, sizeof(sa));
	Length = sizeof(sa);

	ListenSocket = accept(m_Socket, (struct sockaddr *)&sa, &Length);
	// ListenSocket�� Ŭ���̾�Ʈ�� �����û�� �����Ѵ�.
	// m_Socket�� ��� ������ ��������.

	if(ListenSocket == INVALID_SOCKET)
	{
		::MessageBox(NULL, "�� ���� �Ҵ翡 �����߽��ϴ�.", "", MB_OK);
		return 0;
	} // accept���� ������ ���� �ȵǸ�.....

	return ListenSocket;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
BOOL CWSASocket::Initialize(int portno)
{
	m_Socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	// ������ ����� m_Socket�� ����...
	// AF_INET : ���ͳ� �ּ� ���, SOCK_STREAM : ���� Ư��. 
    // IPPROTO_TCP : ���ϰ� �� ��Ʈ���� ����ϴ� ��������
	// WSA_FLAG_OVERLAPPED : ���� ���.

	if(m_Socket == INVALID_SOCKET)
	{
		::MessageBox(NULL, "Listen Socket ���� ����!", NULL, MB_OK);
		return FALSE;
	}

	// ���� ���Ͽ� �ʿ��� Listen Socket -> ���� �䱸�� ��ٸ�

	SOCKADDR_IN * pSock_sin = new SOCKADDR_IN;  // (�ý��� �ּҿ� ���� �ּ� ����)

	pSock_sin->sin_family = AF_INET;
	pSock_sin->sin_addr.S_un.S_addr = INADDR_ANY; // ������ �������� ����� ���� ��� ���� IP�� ���� �ɼ�
	pSock_sin->sin_port = htons(portno);           // ���ø����̼��� �� ��Ʈ�� ������ ����

	// ���ε� �۾�
	// ������ �ý��� �ּҿ� ���� ������ ����
	if(bind (m_Socket, (struct sockaddr FAR *) pSock_sin, sizeof(struct sockaddr)) == SOCKET_ERROR)
	{
		::MessageBox(NULL, "���� ���ε� ����.", NULL, MB_OK);
		return FALSE;
	}

	delete pSock_sin;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////
// Listen Socket ó��
BOOL CWSASocket::Listen()
{
	if(listen(m_Socket, 5) != 0)
	{
		::MessageBox(NULL, "���� ���� ����", "", MB_OK);
		return FALSE;
	}

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
// �б� ���۷κ��� ������ �б�
int CWSASocket::RecvMsg(SOCKET sock, char *buf)
{
	UINT i=0;
	DWORD dwTotalByte;
	int nRecvByte;
	ioctlsocket(sock, FIONREAD, &dwTotalByte);

	while(!(i == dwTotalByte))
	{
		nRecvByte = recv(sock, &buf[i], dwTotalByte-1, 0);
		i += nRecvByte;
	}

	return dwTotalByte;
}

//////////////////////////////////////////////////////////////////////////
// ���� ���۷� �����͸� ����.
// �⺻������ 4����Ʈ�� �迭�� ������.
BOOL CWSASocket::SendMsg(SOCKET sock, LPCSTR buf, int size)
{
 	int result = send(sock, buf, size, 0);

	if(result == SOCKET_ERROR)
	{
		::MessageBox(NULL, "���� : Send����", "", MB_OK);
		return FALSE;
	}

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
// ����Ǿ����� �������� (Ŭ���̾�Ʈ)
BOOL CWSASocket::Connect(char *szHost, int Portno)
{
	SOCKET sock;          
	hostent* host;
	sockaddr_in sa;

	if((host = gethostbyname(szHost)) == NULL )
	{
		::MessageBox(NULL, "Get Host By Name ERROR!!", "", MB_OK);
		return FALSE;
	}

	sa.sin_family = AF_INET;
	sa.sin_port = htons(Portno);
	sa.sin_addr = *((struct in_addr *)host->h_addr_list[0]);

	sock = socket(AF_INET, SOCK_STREAM, 0); // ���� ����.

	int result = connect(sock, (struct sockaddr *)&sa, 16);

	if (result == SOCKET_ERROR)
	{
		if(WSAGetLastError() == WSAEWOULDBLOCK){}
		else return FALSE;
	}

	m_Socket = sock;

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////
// ���� ��ŸƮ �� (���� DLL �ε�)
BOOL CWSASocket::InitSock()
{
	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD(2, 2);

	int error = WSAStartup(wVersionRequested, &wsaData);

	if (error != 0)
	{
		::MessageBox(NULL, "DLL �ʱ�ȭ ����...", "", MB_OK);
		return FALSE;
	}

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) !=2 )
	{
		::MessageBox(NULL, "Winsock DLL 2.2 ���� ����", "���� ����", MB_OK);
		WSACleanup();

		return FALSE;
	}
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////
//
void CWSASocket::Close()
{
	closesocket(m_Socket);
	WSACleanup();
}
