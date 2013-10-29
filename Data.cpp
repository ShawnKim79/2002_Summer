// Data.cpp : implementation file
//

#include "stdafx.h"
#include "MainProject.h"
#include "Data.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CData - 각 점들의 좌표와 펜 색을 저장하는 객체.

CData::CData()
{

}

CData::~CData()
{
}

void CData::Serialize(CArchive &ar)
{
	if (ar.IsStoring())
	{
		ar << m_ptHead;
		ar << m_ptTail;
		ar << m_colorPen;
	}
	else
	{
		ar >> m_ptHead;
		ar >> m_ptTail;
		ar >> m_colorPen;
	}
}

///////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////

// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CData, CObject)
	//{{AFX_MSG_MAP(CData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CData member functions
