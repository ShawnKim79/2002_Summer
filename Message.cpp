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
	m_nMsgLength = 0;   // 패킷 초기 길이.
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
//	Sender(보내는 쪽 처리)

//  패킷 내 데이터 삽입 함수
void CMessage::Put_Data(void *data, int length) // 인자는 삽입될 데이터의 포인터, 데이터의 길이
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

void CMessage::CloseMsg()							// 메세지 닫기(메세지의 길이를 정함-한계두기)
{
	m_Msg.PHEADER.Message_Length = m_nMsgLength;
}

/////////////////////////////////////////////////////////////
//  Binder(받는쪽 처리)

//  길이 얻기 	
int CMessage::Get_DataSize()				// 데이터 길이 추출
{
	return m_Msg.PHEADER.Message_Length;
}

int CMessage::Get_msgLength()				// 메세지 길이 추출
{
	return m_Msg.PHEADER.Message_Length;
}

char *CMessage::Get_DataPtr()				// 메세지 부분 포인터 추출 (리턴값이 포인터이다)
{											// 전체 객체에서 메세지 패킷만 리턴되서 가는것임.
	return (char *)&m_Msg;
}

// 패킷 타입 얻기
BYTE CMessage::GetMsgType()
{
	return m_Msg.PHEADER.Message_type;
}

SOCKET CMessage::GetSocket()
{
	return m_Socket;
}


//char *GetSender();                       // 



