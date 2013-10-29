// Message.cpp: implementation of the CMessage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MainProject.h"
#include "Message.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMessage::CMessage()
{
	m_nMsgLength = 0;   // ��Ŷ �ʱ� ����.
}

CMessage::~CMessage()
{

}

////////////////////////////////////////////////////////////////////
void CMessage::SetSocket(SOCKET s)
{
	m_Socket = s;
}


//////////////////////////////////////////////////////////////////////
//	Sender(������ �� ó��)

//  ��Ŷ �� ������ ���� �Լ�
void CMessage::Put_Data(void *data, int length) // ���ڴ� ���Ե� �������� ������, �������� ����
{
	memcpy(m_Msg.PACKET+5, data, length);
	m_nMsgLength += length;
	//m_Msg.PACKET[m_nMsgLength] = NULL;
}


void CMessage::Set_Header(char type)
{
	m_Msg.PHEADER.Message_type = type;
	m_nMsgLength++;
}

void CMessage::CloseMsg()							// �޼��� �ݱ�(�޼����� ���̸� ����-�Ѱ�α�)
{
	m_Msg.PHEADER.Message_Length = m_nMsgLength;
}

/////////////////////////////////////////////////////////////
//  Binder(�޴��� ó��)

//  ���� ��� 	
int CMessage::Get_DataSize()				// ������ ���� ����
{
	return m_Msg.PHEADER.Message_Length;
}

int CMessage::Get_msgLength()				// �޼��� ���� ����
{
	return m_Msg.PHEADER.Message_Length;
}

char *CMessage::Get_DataPtr()				// �޼��� �κ� ������ ���� (���ϰ��� �������̴�)
{											// ��ü ��ü���� �޼��� ��Ŷ�� ���ϵǼ� ���°���.
	return (char *)&m_Msg;
}

// ��Ŷ Ÿ�� ���
BYTE CMessage::GetMsgType()
{
	return m_Msg.PHEADER.Message_type;
}

SOCKET CMessage::GetSocket()
{
	return m_Socket;
}


//char *GetSender();                       // 



