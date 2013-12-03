// DemoDoc.h : interface of the CDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEMODOC_H__FADD8E70_7BC6_42EF_B0CC_5A198507A232__INCLUDED_)
#define AFX_DEMODOC_H__FADD8E70_7BC6_42EF_B0CC_5A198507A232__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

////////////////for folder open batch matching//////////////////
#include "list"
using namespace std; 
typedef list<CString> FileString;
////////////////////////////////////////////////////////////////

class CDemoDoc : public CDocument
{
protected: // create from serialization only
	CDemoDoc();
	DECLARE_DYNCREATE(CDemoDoc)

// Attributes
public:
	MV_ID image;
	BOOL flag;
	FileString m_folderroot; //Folder multiple target linkedlists
	CString lastfilePath;  //Memorize the file directory this time
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDemoDoc)
	afx_msg void OnOpenfolder();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMODOC_H__FADD8E70_7BC6_42EF_B0CC_5A198507A232__INCLUDED_)
