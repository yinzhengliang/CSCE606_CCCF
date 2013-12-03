#if !defined(AFX_DLGFEATMATCH_H__65D81353_F1F0_4F71_94CD_51B71A77DB5A__INCLUDED_)
#define AFX_DLGFEATMATCH_H__65D81353_F1F0_4F71_94CD_51B71A77DB5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFeatMatch.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgFeatMatch dialog
class CDemoView;                            //step FIVE

class CDlgFeatMatch : public CDialog
{
// Construction
public:
	CDemoView * m_pView;
	CDlgFeatMatch(CWnd* pParent = NULL);   // standard constructor
	CDlgFeatMatch(CDemoView *pView);        //step six
	BOOL Create();
	~CDlgFeatMatch();
// Dialog Data
	//{{AFX_DATA(CDlgFeatMatch)
	enum { IDD = IDD_FEAT_MATCH };
	int		m_modellength;
	int		m_modelwidth;
	int		m_modelx;
	int		m_modely;
	double	m_posx;
	double	m_posy;
	double	m_time;
	int		m_grayfactor;
	BOOL	m_wholeimage;
	int		m_troix;
	int		m_troiy;
	int		m_troilength;
	int		m_troiwidth;
	BOOL	m_wholetarget;
	double	m_acceptance;
	double	m_score;
	//}}AFX_DATA

	MV_ID m_model;
	MV_ID m_image;

	MV_ID featparam;
	MV_ID featmodel;
	MV_ID featresult;

	BOOL m_allmodel;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFeatMatch)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgFeatMatch)
	afx_msg void OnTrain();
	afx_msg void OnMatchsingle();
	afx_msg void OnLocatemodel();
	afx_msg void OnMatchmulti();
	afx_msg void OnLocateroi();
	virtual void OnOK();
	afx_msg void OnLoadModel();
	afx_msg void OnSaveModel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFEATMATCH_H__65D81353_F1F0_4F71_94CD_51B71A77DB5A__INCLUDED_)

