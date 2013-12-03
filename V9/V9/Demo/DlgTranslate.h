#if !defined(AFX_DLGTRANSLATE_H__2CDC328B_DBD1_49CC_B401_C47436B1F130__INCLUDED_)
#define AFX_DLGTRANSLATE_H__2CDC328B_DBD1_49CC_B401_C47436B1F130__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTranslate.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTranslate dialog

class CDlgTranslate : public CDialog
{
// Construction
public:
	CDlgTranslate(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTranslate)
	enum { IDD = IDD_DLG_IM_TRANSLATE };
	double	m_translate_X;
	double	m_translate_Y;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTranslate)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTranslate)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRANSLATE_H__2CDC328B_DBD1_49CC_B401_C47436B1F130__INCLUDED_)
