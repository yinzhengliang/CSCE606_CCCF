#if !defined(AFX_DLGTHRESHOLD_H__68DECE8B_AC68_48C6_9F36_5256B3B3B7B1__INCLUDED_)
#define AFX_DLGTHRESHOLD_H__68DECE8B_AC68_48C6_9F36_5256B3B3B7B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgThreshold.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgThreshold dialog

class CDlgThreshold : public CDialog
{
// Construction
public:
	int flag;
	CDlgThreshold(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgThreshold)
	enum { IDD = IDD_THRESHOLD };
	double	m_threshold;
	int		m_iterate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgThreshold)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgThreshold)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTHRESHOLD_H__68DECE8B_AC68_48C6_9F36_5256B3B3B7B1__INCLUDED_)
