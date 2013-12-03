// DlgFeatMatch.cpp : implementation file
//

#include "stdafx.h"
#include "demo.h"
#include "DlgFeatMatch.h"
#include "DemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFeatMatch dialog


CDlgFeatMatch::CDlgFeatMatch(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFeatMatch::IDD, pParent)
{

}

CDlgFeatMatch::CDlgFeatMatch(CDemoView *pView)
{	
	m_pView = pView;
	//{{AFX_DATA_INIT(CDlgFeatMatch)
	m_modellength = 0;
	m_modelwidth = 0;
	m_modelx = 0;
	m_modely = 0;
	m_posx = 0.0;
	m_posy = 0.0;
	m_time = 0.0;
	m_grayfactor = 120;
	m_wholeimage =FALSE;
	m_troix = 0;
	m_troiy = 0;
	m_troilength = 0;
	m_troiwidth = 0;
	m_wholetarget =TRUE;
	m_acceptance = 0.6;
	m_score = 0.0;
	//}}AFX_DATA_INIT
	//m_pDlgFeatMatch = new CDlgFeatMatch(this);  //step four
	m_model=NULL;
	m_image=NULL;
	m_allmodel=FALSE;
	featparam=NULL;
	featmodel=NULL;
	featresult=NULL;
}

CDlgFeatMatch::~CDlgFeatMatch()
{	
	if(featmodel)
	{
		mvFeatModelFree(featmodel,featparam);
		featmodel=NULL;
	}
	if(featparam)
	{
		mvFeatParamFree(featparam);
		featparam=NULL;
	}
	if(featresult)
	{
		mvFeatResultFree(featresult);
		featresult=NULL;
	}
}


BOOL CDlgFeatMatch::Create()
{
	return CDialog::Create(CDlgFeatMatch::IDD);
}


void CDlgFeatMatch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFeatMatch)
	DDX_Text(pDX, IDC_MODELLENGHT, m_modellength);
	DDX_Text(pDX, IDC_MODELWIDTH, m_modelwidth);
	DDX_Text(pDX, IDC_MODELX, m_modelx);
	DDX_Text(pDX, IDC_MODELY, m_modely);
	DDX_Text(pDX, IDC_POSX, m_posx);
	DDX_Text(pDX, IDC_POSY, m_posy);
	DDX_Text(pDX, IDC_TIME, m_time);
	DDX_Text(pDX, IDC_GRAYFACTOR, m_grayfactor);
	DDX_Check(pDX, IDC_WHOLEIMAGE, m_wholeimage);
	DDX_Text(pDX, IDC_TROIX, m_troix);
	DDX_Text(pDX, IDC_TROIY, m_troiy);
	DDX_Text(pDX, IDC_TROILENGTH, m_troilength);
	DDX_Text(pDX, IDC_TROIWIDTH, m_troiwidth);
	DDX_Check(pDX, IDC_WHOLETARGET, m_wholetarget);
	DDX_Text(pDX, IDC_ACCEPTANCE, m_acceptance);
	DDX_Text(pDX, IDC_SCORE1, m_score);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFeatMatch, CDialog)
	//{{AFX_MSG_MAP(CDlgFeatMatch)
	ON_BN_CLICKED(IDC_TRAIN, OnTrain)
	ON_BN_CLICKED(IDC_MATCHSINGLE, OnMatchsingle)
	ON_BN_CLICKED(IDC_LOCATEMODEL, OnLocatemodel)
	ON_BN_CLICKED(IDC_MATCHMULTI, OnMatchmulti)
	ON_BN_CLICKED(IDC_LOCATEROI, OnLocateroi)
	ON_BN_CLICKED(IDC_LoadModel, OnLoadModel)
	ON_BN_CLICKED(IDC_SaveModel, OnSaveModel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFeatMatch message handlers

void CDlgFeatMatch::OnLocatemodel() 
{
	// TODO: Add your control notification handler code here
	m_modelx=m_pView->m_ModelRect.m_rect.left;
	m_modely=m_pView->m_ModelRect.m_rect.top;
	m_modelwidth=m_pView->m_ModelRect.m_rect.right-m_pView->m_ModelRect.m_rect.left;
	m_modellength=m_pView->m_ModelRect.m_rect.bottom-m_pView->m_ModelRect.m_rect.top;
	m_wholeimage =FALSE;
	UpdateData(FALSE);
}

void CDlgFeatMatch::OnLocateroi() 
{
	// TODO: Add your control notification handler code here
	m_troix=m_pView->m_ModelRect.m_rect.left;
	m_troiy=m_pView->m_ModelRect.m_rect.top;
	m_troiwidth=m_pView->m_ModelRect.m_rect.right-m_pView->m_ModelRect.m_rect.left;
	m_troilength=m_pView->m_ModelRect.m_rect.bottom-m_pView->m_ModelRect.m_rect.top;
	m_wholetarget =FALSE;
	UpdateData(FALSE);

	CDC* mpDC =m_pView->GetDC();        // Obtain display control's DC
    HDC mhDC = mpDC ->GetSafeHdc();   
	
	CPen yellowpen;
	yellowpen.CreatePen(PS_SOLID, 1, RGB(0, 255, 255));
	CPen* pOldPen = mpDC->SelectObject(&yellowpen);
    	
	mpDC->MoveTo(m_troix,m_troiy);
	mpDC->LineTo(m_troix+m_troiwidth,m_troiy);
	mpDC->MoveTo(m_troix+m_troiwidth,m_troiy);
	mpDC->LineTo(m_troix+m_troiwidth,m_troiy+m_troilength);
	mpDC->MoveTo(m_troix+m_troiwidth,m_troiy+m_troilength);
	mpDC->LineTo(m_troix,m_troiy+m_troilength);
	mpDC->MoveTo(m_troix,m_troiy+m_troilength);
	mpDC->LineTo(m_troix,m_troiy);
	
    mpDC->SelectObject(pOldPen); 
    ReleaseDC( mpDC );
}

void CDlgFeatMatch::OnTrain() 
{
	// TODO: Add your control notification handler code here
	m_model=m_pView->GetDocument()->image;
	if(!m_model) 
	{
		MessageBox("No image available!");
		return;
	}

	if(featmodel)
	{
		mvFeatModelFree(featmodel,featparam);
		featmodel=NULL;
	}
	if(featparam)
	{
		mvFeatParamFree(featparam);
		featparam=NULL;
	}
	if(featresult)
	{
		mvFeatResultFree(featresult);
		featresult=NULL;
	}

    featparam=mvFeatAllocParam(MV_FEATMATCH_EDGE);
	//featparam=mvFeatAllocParam(MV_DEFAULT);
    
    UpdateData(TRUE);  //Inputs from controls
	if(m_grayfactor<=20||m_grayfactor>=255)
	{
        m_grayfactor=120;
	}
    mvSetFeatParam(MV_GRAYFACTOR,m_grayfactor,featparam);
	if (m_wholeimage)
	{
		featmodel=mvFeatAllocModel(m_model,featparam);
	}	
	else	
	{
		m_pView->m_ModelRect.m_rect.left=m_modelx;
		m_pView->m_ModelRect.m_rect.top=m_modely;
		m_pView->m_ModelRect.m_rect.right=m_modelx+m_modelwidth;
		m_pView->m_ModelRect.m_rect.bottom=m_modely+m_modellength;
		m_pView->Invalidate();
        
		mvSetFeatParam(MV_MODEL_X,m_modelx,featparam);
		mvSetFeatParam(MV_MODEL_Y,m_modely,featparam);
		mvSetFeatParam(MV_MODELROI_X,m_modelwidth,featparam);
	    mvSetFeatParam(MV_MODELROI_Y,m_modellength,featparam);
		mvSetFeatParam(MV_ACCEPTANCE,m_acceptance,featparam);
        featmodel=mvFeatAllocModel(m_model,featparam);
	}

	featresult=mvFeatAllocResult(featparam);
	mvFeatPreprocess(featmodel,featparam);
 
	CDC* pDC =GetDlgItem(IDC_MODELIMAGE) ->GetDC();        // obtain display control's DC
    HDC hDC = pDC ->GetSafeHdc();                // Obtain HDC(Device Handler) for drawing operations
	CRect rect;
	GetDlgItem(IDC_MODELIMAGE) ->GetClientRect( &rect );
	mvFeatDrawModel(m_model,featparam,hDC,&rect);
}

void CDlgFeatMatch::OnSaveModel() 
{
	// TODO: Add your control notification handler code here
	CFileDialog FDlg(TRUE , ".ftmo" , NULL ,OFN_HIDEREADONLY, "ftmo文件(*.ftmo)|*.ftmo|所有文件(*.*) |*.*||" );
	CString filePath;		
	if(FDlg.DoModal() == IDOK)
	{
		filePath = FDlg.GetPathName();
		UpdateData(false);
		filePath.Replace("\\","\\\\");
		//mvTempSave(filePath,m_Model);
        UpdateData(TRUE);
        mvFeatModelSave(filePath,m_model,featparam);
	}
}

void CDlgFeatMatch::OnLoadModel() 
{
	// TODO: Add your control notification handler code here
	CFileDialog FDlg(TRUE , ".ftmo" , NULL , OFN_HIDEREADONLY , "File(*.ftmo)|*.ftmo|All Files(*.*) |*.*||" );
	CString filePath;		
	if(FDlg.DoModal() == IDOK)
	{
		filePath = FDlg.GetPathName();
		UpdateData(false);
		filePath.Replace("\\","\\\\");
		mvFeatModelLoad(filePath,&m_model,&featparam);
	}

	if(!m_model) 
	{
		MessageBox("No image available! Loading failure!");
		return;
	}
	CDC* pDC =GetDlgItem(IDC_MODELIMAGE) ->GetDC();        // Obtain display control's DC
    HDC hDC = pDC ->GetSafeHdc();                // Obtain HDC(Device Handler) for drawing operations
	CRect rect;
	GetDlgItem(IDC_MODELIMAGE) ->GetClientRect( &rect );
	mvFeatDrawModel(m_model,featparam,hDC,&rect);

	if(featmodel)
	{
		mvFeatModelFree(featmodel,featparam);
		featmodel=NULL;
	}
	featmodel=mvFeatAllocModel(m_model,featparam);
	
	if(featresult)
	{
		mvFeatResultFree(featresult);
		featresult=NULL;
	}

	featresult=mvFeatAllocResult(featparam);
	mvFeatPreprocess(featmodel,featparam);
}

void CDlgFeatMatch::OnMatchsingle() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);  //Inputs from controls
    m_image=m_pView->GetDocument()->image;
	
	if (m_image==NULL)
	{
		MessageBox("Input image!");
		return;
	}
	if (featmodel==NULL)
	{
		MessageBox("Train model!");
		return;
	}
	
    if(!m_wholetarget)
	{        
		mvSetFeatParam(MV_TARGET_X,m_troix,featparam);
		mvSetFeatParam(MV_TARGET_Y,m_troiy,featparam);
		mvSetFeatParam(MV_TARGETROI_X,m_troiwidth,featparam);
		mvSetFeatParam(MV_TARGETROI_Y,m_troilength,featparam);
		mvSetFeatParam(MV_ACCEPTANCE,m_acceptance,featparam);

       	CDC* mpDC =m_pView->GetDC();        // Obtain display control's DC
		HDC mhDC = mpDC ->GetSafeHdc();   
		
		CPen yellowpen;
		yellowpen.CreatePen(PS_SOLID, 1, RGB(0, 255, 255));
		CPen* pOldPen = mpDC->SelectObject(&yellowpen);
		
		mpDC->MoveTo(m_troix,m_troiy);
		mpDC->LineTo(m_troix+m_troiwidth,m_troiy);
		mpDC->MoveTo(m_troix+m_troiwidth,m_troiy);
		mpDC->LineTo(m_troix+m_troiwidth,m_troiy+m_troilength);
		mpDC->MoveTo(m_troix+m_troiwidth,m_troiy+m_troilength);
		mpDC->LineTo(m_troix,m_troiy+m_troilength);
		mpDC->MoveTo(m_troix,m_troiy+m_troilength); 
		mpDC->LineTo(m_troix,m_troiy);
		
		mpDC->SelectObject(pOldPen); 
        ReleaseDC( mpDC );
	}
	if(m_wholetarget)
	{
		mvSetFeatParam(MV_TARGET_X,MV_DEFAULT,featparam);
		mvSetFeatParam(MV_TARGET_Y,MV_DEFAULT,featparam);
		mvSetFeatParam(MV_TARGETROI_X,MV_DEFAULT,featparam);
		mvSetFeatParam(MV_TARGETROI_Y,MV_DEFAULT,featparam);
		mvSetFeatParam(MV_ACCEPTANCE,m_acceptance,featparam);
	}

	double t1=(double)mvGetTickCount();
    if(!mvFeatFind(m_image,featmodel,featparam,featresult))
	{
		MessageBox("No match image found!");
		return;
	}
	double t2=(double)mvGetTickCount();
	m_time=(t2-t1)/mvGetTickFrequency()*1000;
	
	mvFeatGetResult(featresult,MV_RESULT_X,&m_posx);
	mvFeatGetResult(featresult,MV_RESULT_Y,&m_posy);
	mvFeatGetResult(featresult,MV_RESULT_SCORE,&m_score);

	
	UpdateData(FALSE);
    

	CDC* mpDC =m_pView->GetDC();        // Obtain display control's DC
    HDC mhDC = mpDC ->GetSafeHdc();   

	CPen greenpen;
	greenpen.CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	CPen* pOldPen = mpDC->SelectObject(&greenpen);
    
	int rx=m_modelwidth/2;
	int ry=m_modellength/2;

	mpDC->MoveTo(m_posx-rx,m_posy-ry);
	mpDC->LineTo(m_posx+rx,m_posy-ry);
	mpDC->MoveTo(m_posx+rx,m_posy-ry);
	mpDC->LineTo(m_posx+rx,m_posy+ry);
	mpDC->MoveTo(m_posx+rx,m_posy+ry);
	mpDC->LineTo(m_posx-rx,m_posy+ry);
	mpDC->MoveTo(m_posx-rx,m_posy+ry);
	mpDC->LineTo(m_posx-rx,m_posy-ry);
	
    mpDC->SetPixel(m_posx,m_posy,RGB(0,255,0));
	mpDC->MoveTo(m_posx-3,m_posy);
	mpDC->LineTo(m_posx+4,m_posy);
	mpDC->MoveTo(m_posx,m_posy-3);
	mpDC->LineTo(m_posx,m_posy+4);
	
    mpDC->SelectObject(pOldPen); 
    ReleaseDC( mpDC );
}

void CDlgFeatMatch::OnMatchmulti() 
{
	// TODO: Add your control notification handler code here
    UpdateData();  // Inputs from controls

   	if (featmodel==NULL)
	{
		MessageBox("Train model!");
		return;
	}

	int all=m_pView->m_pDoc->m_folderroot.size();
	double *m_featpos_x=new double [all];
	double *m_featpos_y=new double [all];
//	double *m_featangle=new double [all];
	double *m_featscore=new double [all];
	double *m_feattime=new double [all];

	if(!m_wholetarget)
	{        
		mvSetFeatParam(MV_TARGET_X,m_troix,featparam);
		mvSetFeatParam(MV_TARGET_Y,m_troiy,featparam);
		mvSetFeatParam(MV_TARGETROI_X,m_troiwidth,featparam);
		mvSetFeatParam(MV_TARGETROI_Y,m_troilength,featparam);
		mvSetFeatParam(MV_ACCEPTANCE,m_acceptance,featparam);
	}
	if(m_wholetarget)
	{
		mvSetFeatParam(MV_TARGET_X,MV_DEFAULT,featparam);
		mvSetFeatParam(MV_TARGET_Y,MV_DEFAULT,featparam);
		mvSetFeatParam(MV_TARGETROI_X,MV_DEFAULT,featparam);
		mvSetFeatParam(MV_TARGETROI_Y,MV_DEFAULT,featparam);
		mvSetFeatParam(MV_ACCEPTANCE,m_acceptance,featparam);
	}

	FileString::iterator count;
	int i;
	double t1;
	double t2;
	for(count=m_pView->m_pDoc->m_folderroot.begin(),i=0;count!=m_pView->m_pDoc->m_folderroot.end();i++,count++)
	{
        mvReadImageFile(&m_image,(*count).GetBuffer(0));

		t1=(double)mvGetTickCount();
		if(!mvFeatFind(m_image,featmodel,featparam,featresult))
		{
			m_featpos_x[i]=-1;
			m_featpos_y[i]=-1;
			m_feattime[i]=-1;
			m_featscore[i]=-1;
		}
		else
		{
			t2=(double)mvGetTickCount();
			mvFeatGetResult(featresult,MV_RESULT_X,&m_featpos_x[i]);
			mvFeatGetResult(featresult,MV_RESULT_Y,&m_featpos_y[i]);
			mvFeatGetResult(featresult,MV_RESULT_SCORE,&m_featscore[i]);
			m_feattime[i]=(t2-t1)/mvGetTickFrequency()*1000;
		}
        
		mvReleaseImage(m_image);
	}
	 	 CString strFileName = "G:\\myresult.txt";
		 CFile file ;
         file.Open(strFileName,CFile::modeCreate|CFile::modeReadWrite);
		 CString str;
  
		 str="No.\t";
		 file.Write((LPCTSTR)str,str.GetLength());

		 str="CoordinateX\t\t";
		 file.Write((LPCTSTR)str,str.GetLength());

		 str="CoordinateY\t\t";
		 file.Write((LPCTSTR)str,str.GetLength());

		 str="Score\t\t";
		 file.Write((LPCTSTR)str,str.GetLength());

         str="Time\t\t";
		 file.Write((LPCTSTR)str,str.GetLength());

		 str="File Path\r\n";
		 file.Write((LPCTSTR)str,str.GetLength());

         count=m_pView->m_pDoc->m_folderroot.begin();
		 for(int f=0;f<all;f++)
		 {
			 str.Format("%d\t",f);
			 file.Write((LPCTSTR)str,str.GetLength());
			 
			 str.Format("%f\t",m_featpos_x[f]);
			 file.Write((LPCTSTR)str,str.GetLength());
			 
			 str.Format("%f\t",m_featpos_y[f]);
			 file.Write((LPCTSTR)str,str.GetLength());
			 
			 str.Format("%f",m_featscore[f]);
			 file.Write((LPCTSTR)str,str.GetLength());
			 file.Write("\t",1); 
			 
			 str.Format("%f\t",m_feattime[f]);
			 file.Write((LPCTSTR)str,str.GetLength());

			 str.Format("%s\r\n",*(count++));
			 file.Write((LPCTSTR)str,str.GetLength());
		 }
		 
		 file.Close();
		 
		 delete []m_featpos_x;
		 delete []m_featpos_y;
//		 delete []m_featscore;
		 delete []m_feattime;
//		 delete []m_featangle;

		 MessageBox("finished!");
}


void CDlgFeatMatch::OnOK() 
{
	// TODO: Add extra validation here
	m_pView->m_bDrawModelRect=FALSE;
	m_pView->Invalidate();
	CDialog::OnOK();
}


