// Message.h: interface for the CMessage class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include "winsock2.h"

/***************************************
0x0000 for broadcasting Mssages

0x0001 ~ 0x00ff : Server Messages
0x0100 ~ 0xff00 : Client Messages
*****************************************/

#define MAX_LENGTH 	    10000   // 메세지의 최대 길이
#define PACKETSIZE		10000   // 패킷 싸이즈
#define NAMELENGTH		20      // 이름 길이
// #define IDLENGTH		20      // ID 길이
#define PASSWDLENGTH	20      // Password 길이

#define HEADERSIZE      sizeof(PACKETHEADER)

//////////////////////////////////////////////////////////////////////
// types of ChatServer Message   (Server가 보내는 메세지)

// 접속시
#define SM_CONNECTED  0x0001	// 최초 클라이언트 접속시 접속 허가
#define SM_AUTHENOK   0x0002	// 클라이언트에 대한 의 인증 성공
#define SM_INVALCONN  0x0003    // 클라이언트 인증실패 (사실상의 연결 실패)
// 클라이언트 인증은........없어도 된다. 일단은. 

// 채팅
#define SM_NORMSG     0X0010 	// 채팅 메세지
#define SM_ACKJOIN    0x0011	// 채팅방 참가
#define SM_ACKLEAVE   0X0012	// 채팅방 퇴장

// 그래픽
#define SM_LINE       0x0020    // 일직선
#define SM_FREELINE   0x0021    // 프리 라인
#define SM_RACTANGLE  0x0022    // 네모
#define SM_CIRCLE     0x0023    // 원

// 파일전송
#define SM_TEXTTRANS  0x0030    // 텍스트 파일 전송

////////////////////////////////////////////////////////////////////////////////
// types of ChatClient Message   (클라이언트가 보내는 메세지)

// 접속시
#define CM_REQAUTH        0x0100	// 인증 요청

#define CM_REQWAITROOM    0x0200	// 대기실 정보 요청
#define CM_REQROOMS       0x0300	// 개설된 방 정보 요청

// 새로운 방 개설
#define CM_REQMKROOM      0x0400	// 새로운 방 개설
#define CM_NORMSG         0x1000	// 채팅 메세지
#define CM_WHISPER        0X1100	// 귓속말
#define CM_REQJOIN        0X1200	// 방 입장 요청
#define CM_REQLEAVE       0X1300	// 방 퇴장 요청
#define CM_SMALLPAPER     0X1400	// 쪽지

// 그래픽
#define CM_LINE           0x2000    // 일직선
#define CM_FREELINE       0x2100    // 프리 라인
#define CM_RACTANGLE      0x2200    // 네모
#define CM_CIRCLE         0x2300    // 원

// 파일전송
#define CM_TEXTTRANS      0x3000    // 텍스트 파일 전송

#pragma pack(push)
#pragma pack(1)

typedef struct
{
	char Message_type;              // 메세지 타입
	int  Message_Length;			// 메세지 길이
} PACKETHEADER, *LPPACKETHEADER;

typedef union
{
	PACKETHEADER PHEADER;
	BYTE PACKET[MAX_LENGTH]; // 실제 메세지 내용이 저장되는 배열.
} MESSAGE;
// MESSAGE형(공용체) 정의
// MESSAGE형 내부에서 헤더와 실제 PACKET배열의 시작 주소는 동일하다...(union)
// 메세지는 패킷 헤더와 실제 패킷(길이 10000바이트짜리 배열)

#pragma pack(pop)

class CMessage  
{
public:
// 소켓 설정
	SOCKET GetSocket();                      // 
	void SetSocket(SOCKET sock);             //	메세지 객체와 소켓을 연결.

//////////////////////////
//	Sender(보내는 쪽 처리)

//  패킷 내 데이터 삽입 함수
	void Put_Data(void *data, int length);	// 인자는 삽입될 데이터의 포인터, 데이터의 길이
	void Set_Header(char type);             // type은 미리 define해둔 메세지 타입.
	void CloseMsg();						// 메세지 닫기(메세지의 길이를 정함-한계두기)

///////////////////////
//  Binder(받는쪽 처리)

//  길이 얻기 	
	int Get_DataSize();						// 데이터 길이 추출
	int Get_msgLength();					// 메세지 길이 추출
	char *Get_DataPtr();					// 메세지 데이터 부분 포인터 추출 (리턴값이 포인터이다)

// 패킷 타입 얻기
	BYTE GetMsgType();

	//char *GetSender();                       // 

/////////////////////////////////////////////////////////////////////////////////
// 생성자와 소멸자
	CMessage();
	virtual ~CMessage();

private:
	SOCKET m_Socket;				  // 메세지의 소켓.
	MESSAGE m_Msg;                    // 생성한 메세지
	int m_nMsgLength;				  // 작업중 저장(계산)되는 메세지의 길이.

};


#endif