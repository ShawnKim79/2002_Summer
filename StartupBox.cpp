// StartupBox.cpp : implementation file
//

#include "stdafx.h"
#include "MainProject.h"
#include "StartupBox.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStartupBox dialog


CStartupBox::CStartupBox(CWnd* pParent /*=NULL*/)
	: CDialog(CStartupBox::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStartupBox)
	m_StartSwitch = 0;
	//}}AFX_DATA_INIT
}


void CStartupBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStartupBox)
	DDX_Radio(pDX, IDC_RADIOSERVER, m_StartSwitch);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStartupBox, CDialog)
	//{{AFX_MSG_MAP(CStartupBox)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIOSERVER, IDC_RADIOCLIENT, OnRadioserver)
	ON_BN_CLICKED(IDC_OK, OnOk)
	ON_BN_CLICKED(IDC_CANCEL, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// CStartupBox message handlers

void CStartupBox::OnRadioserver() 
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);
	
	CRect rect;
	GetWindowRect(&rect);

	// 1일때 : 클라이언트
	if(m_StartSwitch)
	{
		SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height()+150, SWP_NOZORDER | SWP_NOMOVE);
		GetDlgItem(IDC_IP_ADDRESS)->EnableWindow(TRUE);
		GetDlgItem(IDC_PORT_NO)->EnableWindow(TRUE);
	}
	else  // 0일때 : 서버
	{
		SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height()-150, SWP_NOZORDER | SWP_NOMOVE);
		GetDlgItem(IDC_IP_ADDRESS)->EnableWindow(FALSE);
		GetDlgItem(IDC_PORT_NO)->EnableWindow(FALSE);
	}
	
	UpdateData(FALSE);

}

void CStartupBox::OnOk() 
{
	GetDlgItemText(IDC_IP_ADDRESS, m_strIP);
	m_nPortno = GetDlgItemInt(IDC_PORT_NO, NULL, FALSE);
	CDialog::OnOK();
}

void CStartupBox::OnCancel() 
{
	CDialog::OnCancel();	
}
