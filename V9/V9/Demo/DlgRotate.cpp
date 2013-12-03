// DlgRotate.cpp : implementation file
//

#include "stdafx.h"
#include "demo.h"
#include "DlgRotate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRotate dialog


CDlgRotate::CDlgRotate(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRotate::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRotate)
	m_rotate_X = 0.0;
	m_rotate_Angle = 0.0;
	m_rotate_Y = 0.0;
	angle=0.0;
	//}}AFX_DATA_INIT
}


void CDlgRotate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRotate)
	DDX_Text(pDX, IDC_ROTATE_X, m_rotate_X);
	DDX_Text(pDX, IDC_ROTATE_ANGLE, m_rotate_Angle);
	DDX_Text(pDX, IDC_ROTATE_Y, m_rotate_Y);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRotate, CDialog)
	//{{AFX_MSG_MAP(CDlgRotate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRotate message handlers

BOOL CDlgRotate::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	((CButton *)GetDlgItem(IDC_ROTATE_DEG))->SetCheck(BST_CHECKED);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRotate::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	if(IDC_ROTATE_RAD==GetCheckedRadioButton(IDC_ROTATE_DEG,IDC_ROTATE_RAD))
		angle=m_rotate_Angle*180/PI;
	else angle=m_rotate_Angle;
	CDialog::OnOK();
}
