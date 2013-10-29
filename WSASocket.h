// WSASocket.h: interface for the CWSASocket class.
//
//////////////////////////////////////////////////////////////////////
// ���� ���� Ŭ����
// �ϴ��� 1:1 ����.

#ifndef _WSASOCKET_H_
#define _WSASOCKET_H_

#include "winsock2.h"
#include "includes.h"

class CWSASocket  
{
public:
	CWSASocket();
	virtual ~CWSASocket();
	BOOL Initialize(int portno);
	SOCKET Accept();

	SOCKET Get_Socket() {return m_Socket;}
	
public:
	void Close();
	BOOL InitSock();
	BOOL Connect(char *szHost, int Portno);
	BOOL SendMsg(SOCKET sock, LPCSTR buf, int size);   // ������ �޼��� ���� �Լ�
	BOOL RecvMsg(SOCKET sock, char *buf);             // �޴� �޼��� ���� �Լ�
	BOOL Listen();                                    // ���� ��� �Լ� 
	SOCKET m_Socket;   //  ������ ����ü(������ �ڵ�� ��޵�)
	                   //  ������ Listen ���Ͽ��� �����û ó��.


};

#endif