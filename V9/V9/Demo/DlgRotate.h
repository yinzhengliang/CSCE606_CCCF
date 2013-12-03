#if !defined(AFX_DLGROTATE_H__4ECFD27F_BDF5_49C0_AC3B_97192D1E80AA__INCLUDED_)
#define AFX_DLGROTATE_H__4ECFD27F_BDF5_49C0_AC3B_97192D1E80AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRotate.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRotate dialog

class CDlgRotate : public CDialog
{
// Construction
public:
	CDlgRotate(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRotate)
	enum { IDD = IDD_DLG_IMROTATE };
	double	m_rotate_X;
	double	m_rotate_Angle;
	double	m_rotate_Y;
	//}}AFX_DATA

	double angle;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRotate)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRotate)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGROTATE_H__4ECFD27F_BDF5_49C0_AC3B_97192D1E80AA__INCLUDED_)
