// DlgThreshold.cpp : implementation file
//

#include "stdafx.h"
#include "demo.h"
#include "DlgThreshold.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgThreshold dialog


CDlgThreshold::CDlgThreshold(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgThreshold::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgThreshold)
	m_threshold = 0;
	m_iterate = -1;
	//}}AFX_DATA_INIT
}


void CDlgThreshold::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgThreshold)
	DDX_Text(pDX, IDC_THRESHOLD, m_threshold);
	DDX_Radio(pDX, IDC_ITERATE, m_iterate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgThreshold, CDialog)
	//{{AFX_MSG_MAP(CDlgThreshold)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgThreshold message handlers


