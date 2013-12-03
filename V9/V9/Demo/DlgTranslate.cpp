// DlgTranslate.cpp : implementation file
//

#include "stdafx.h"
#include "demo.h"
#include "DlgTranslate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTranslate dialog


CDlgTranslate::CDlgTranslate(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTranslate::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTranslate)
	m_translate_X = 0.0;
	m_translate_Y = 0.0;
	//}}AFX_DATA_INIT
}


void CDlgTranslate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTranslate)
	DDX_Text(pDX, IDC_TRANSLATE_X, m_translate_X);
	DDX_Text(pDX, IDC_TRANSLATE_Y, m_translate_Y);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTranslate, CDialog)
	//{{AFX_MSG_MAP(CDlgTranslate)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTranslate message handlers
