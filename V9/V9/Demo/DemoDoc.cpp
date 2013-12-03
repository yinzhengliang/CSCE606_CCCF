// DemoDoc.cpp : implementation of the CDemoDoc class
//

#include "stdafx.h"
#include "Demo.h"

#include "DemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemoDoc

IMPLEMENT_DYNCREATE(CDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CDemoDoc)
	ON_COMMAND(IDM_OPENFOLDER, OnOpenfolder)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoDoc construction/destruction

CDemoDoc::CDemoDoc()
{
	// TODO: add one-time construction code here
	flag=FALSE;
	image=NULL;
	lastfilePath.Empty();
}

CDemoDoc::~CDemoDoc()
{
}

BOOL CDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDemoDoc serialization

void CDemoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDemoDoc diagnostics

#ifdef _DEBUG
void CDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDemoDoc commands

BOOL CDemoDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	if (flag)
	{
		mvReleaseImage(image);
		flag = FALSE;
	}
	
	if(!mvReadImageFile(&image,lpszPathName))
	{
		AfxMessageBox("failed to open image");
		
		return FALSE;
	}
	else
		flag=TRUE;
	
	// TODO: Add your specialized creation code here
	lastfilePath.Format( "%s", lpszPathName);
	return TRUE;
}

BOOL CDemoDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (flag)
	{
		mvWriteImageFile(image,lpszPathName);
	}
	
	return CDocument::OnSaveDocument(lpszPathName);
}

void CDemoDoc::OnOpenfolder() 
{
	// TODO: Add your command handler code here
	BROWSEINFO  bi;
	bi.hwndOwner=NULL;
	bi.pidlRoot=NULL;
	bi.pszDisplayName=NULL;
	bi.lpszTitle=NULL;
	bi.ulFlags=0;
	bi.lpfn =NULL;
	bi.iImage =0;
	LPCITEMIDLIST pidl=SHBrowseForFolder(&bi);
	if(!pidl)
		return;
	TCHAR  szDisplayName[255];
	memset(szDisplayName,0,sizeof(TCHAR)*255);
	SHGetPathFromIDList(pidl,szDisplayName);
	CString path(szDisplayName);
	CString pather;
    
	pather=path+"\\";
	path+= "\\*.*";
	CString	 strFileName,strSuffix;
	int	nIndex;	
	CFileFind    tempFind;
	CString strbmp;

    //ÉùÃ÷countÎªµü´úÆ÷
    FileString::iterator count;
	
	m_folderroot.clear();
	BOOL   bIsFinded   =(BOOL)tempFind.FindFile(path);	
	while(   bIsFinded   ) 
	{ 
		bIsFinded   =   (BOOL)tempFind.FindNextFile();	
		if(!tempFind.IsDots())   
		{ 
			strFileName   =   tempFind.GetFileName(); 
			nIndex   =   strFileName.ReverseFind('.');	         
			strSuffix   =   strFileName.Mid(nIndex+1); 
			strSuffix.MakeUpper(); 
			if(strSuffix== "BMP")   
			{  
				strbmp=pather+strFileName;
				m_folderroot.push_back(strbmp);
			} 
		} 
	} 
    tempFind.Close();
    
// 	//test 
// 	CString strFile = "D:\\BMP.txt";
// 	CFile file ;
// 	file.Open(strFile,CFile::modeCreate|CFile::modeReadWrite);
// 	CString str;
// 	
// 	for(count=m_folderroot.begin(); count!=m_folderroot.end(); ++count)
// 	{
// 		file.Write((*count).GetBuffer(0),(*count).GetLength());
// 		file.Write("\t",1); 
// 	}
// 	file.Write("\r\n",2);
// 	file.Close();
//                 ////////////////////////
}
