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

#define MAX_LENGTH 	    10000   // �޼����� �ִ� ����
#define PACKETSIZE		10000   // ��Ŷ ������
#define NAMELENGTH		20      // �̸� ����
// #define IDLENGTH		20      // ID ����
#define PASSWDLENGTH	20      // Password ����

#define HEADERSIZE      sizeof(PACKETHEADER)

//////////////////////////////////////////////////////////////////////
// types of ChatServer Message   (Server�� ������ �޼���)

// ���ӽ�
#define SM_CONNECTED  0x0001	// ���� Ŭ���̾�Ʈ ���ӽ� ���� �㰡
#define SM_AUTHENOK   0x0002	// Ŭ���̾�Ʈ�� ���� �� ���� ����
#define SM_INVALCONN  0x0003    // Ŭ���̾�Ʈ �������� (��ǻ��� ���� ����)
// Ŭ���̾�Ʈ ������........��� �ȴ�. �ϴ���. 

// ä��
#define SM_NORMSG     0X0010 	// ä�� �޼���
#define SM_ACKJOIN    0x0011	// ä�ù� ����
#define SM_ACKLEAVE   0X0012	// ä�ù� ����

// �׷���
#define SM_LINE       0x0020    // ������
#define SM_FREELINE   0x0021    // ���� ����
#define SM_RACTANGLE  0x0022    // �׸�
#define SM_CIRCLE     0x0023    // ��

// ��������
#define SM_TEXTTRANS  0x0030    // �ؽ�Ʈ ���� ����

////////////////////////////////////////////////////////////////////////////////
// types of ChatClient Message   (Ŭ���̾�Ʈ�� ������ �޼���)

// ���ӽ�
#define CM_REQAUTH        0x0100	// ���� ��û

#define CM_REQWAITROOM    0x0200	// ���� ���� ��û
#define CM_REQROOMS       0x0300	// ������ �� ���� ��û

// ���ο� �� ����
#define CM_REQMKROOM      0x0400	// ���ο� �� ����
#define CM_NORMSG         0x1000	// ä�� �޼���
#define CM_WHISPER        0X1100	// �ӼӸ�
#define CM_REQJOIN        0X1200	// �� ���� ��û
#define CM_REQLEAVE       0X1300	// �� ���� ��û
#define CM_SMALLPAPER     0X1400	// ����

// �׷���
#define CM_LINE           0x2000    // ������
#define CM_FREELINE       0x2100    // ���� ����
#define CM_RACTANGLE      0x2200    // �׸�
#define CM_CIRCLE         0x2300    // ��

// ��������
#define CM_TEXTTRANS      0x3000    // �ؽ�Ʈ ���� ����

#pragma pack(push)
#pragma pack(1)

typedef struct
{
	char Message_type;              // �޼��� Ÿ��
	int  Message_Length;			// �޼��� ����
} PACKETHEADER, *LPPACKETHEADER;

typedef union
{
	PACKETHEADER PHEADER;
	BYTE PACKET[MAX_LENGTH]; // ���� �޼��� ������ ����Ǵ� �迭.
} MESSAGE;
// MESSAGE��(����ü) ����
// MESSAGE�� ���ο��� ����� ���� PACKET�迭�� ���� �ּҴ� �����ϴ�...(union)
// �޼����� ��Ŷ ����� ���� ��Ŷ(���� 10000����Ʈ¥�� �迭)

#pragma pack(pop)

class CMessage  
{
public:
// ���� ����
	SOCKET GetSocket();                      // 
	void SetSocket(SOCKET sock);             //	�޼��� ��ü�� ������ ����.

//////////////////////////
//	Sender(������ �� ó��)

//  ��Ŷ �� ������ ���� �Լ�
	void Put_Data(void *data, int length);	// ���ڴ� ���Ե� �������� ������, �������� ����
	void Set_Header(char type);             // type�� �̸� define�ص� �޼��� Ÿ��.
	void CloseMsg();						// �޼��� �ݱ�(�޼����� ���̸� ����-�Ѱ�α�)

///////////////////////
//  Binder(�޴��� ó��)

//  ���� ��� 	
	int Get_DataSize();						// ������ ���� ����
	int Get_msgLength();					// �޼��� ���� ����
	char *Get_DataPtr();					// �޼��� ������ �κ� ������ ���� (���ϰ��� �������̴�)

// ��Ŷ Ÿ�� ���
	BYTE GetMsgType();

	//char *GetSender();                       // 

/////////////////////////////////////////////////////////////////////////////////
// �����ڿ� �Ҹ���
	CMessage();
	virtual ~CMessage();

private:
	SOCKET m_Socket;				  // �޼����� ����.
	MESSAGE m_Msg;                    // ������ �޼���
	int m_nMsgLength;				  // �۾��� ����(���)�Ǵ� �޼����� ����.

};


#endif