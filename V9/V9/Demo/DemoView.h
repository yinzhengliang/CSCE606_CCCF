// DemoView.h : interface of the CDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEMOVIEW_H__3AC73212_6239_49B9_AAED_FE9199EACC26__INCLUDED_)
#define AFX_DEMOVIEW_H__3AC73212_6239_49B9_AAED_FE9199EACC26__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DemoDoc.h"

#include "mv.h"
#include "DlgFeatMatch.h"  
#include "DlgRotate.h"
#include "DlgTranslate.h"

class CDemoView : public CScrollView
{
protected: // create from serialization only
	CDemoView();
	DECLARE_DYNCREATE(CDemoView)

// Attributes
public:
	CDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	CDemoDoc *m_pDoc;
	CDlgFeatMatch* m_pDlgFeatMatch;
	CRectTracker  m_ModelRect;
	bool   m_bDrawModelRect;
	bool   m_bDrawModelPos;
	bool   m_bDrawPMatchPos;
	bool   m_bDrawGMatchPos;	
	bool   m_bDrawTempResult;	

	virtual ~CDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDemoView)
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnFeatmatch();
	afx_msg void OnErosion();
	afx_msg void OnDilation();
	afx_msg void OnOpening();
	afx_msg void OnClosing();
	afx_msg void OnAverrageFilter3x3();
	afx_msg void OnAverageFilter5();
	afx_msg void OnImFft();;
	afx_msg void OnImRotate();
	afx_msg void OnImTranslate();
	afx_msg void OnMedianFilter3();
	afx_msg void OnMedianFilter5();
	afx_msg void OnSobelFiltertThick();
	afx_msg void OnSobelFilterThin();
	afx_msg void OnEditUndo();
	afx_msg void OnThreshold();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DemoView.cpp
inline CDemoDoc* CDemoView::GetDocument()
   { return (CDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMOVIEW_H__3AC73212_6239_49B9_AAED_FE9199EACC26__INCLUDED_)
