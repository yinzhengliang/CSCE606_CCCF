// DemoView.cpp : implementation of the CDemoView class
//

#include "stdafx.h"
#include "Demo.h"

#include "DemoDoc.h"
#include "DemoView.h"
#include "DlgThreshold.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemoView

IMPLEMENT_DYNCREATE(CDemoView, CScrollView)

BEGIN_MESSAGE_MAP(CDemoView, CScrollView)
	//{{AFX_MSG_MAP(CDemoView)
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(IDM_FEATMATCH, OnFeatmatch)
	ON_COMMAND(IDM_EROSION, OnErosion)
	ON_COMMAND(IDM_DILATION, OnDilation)
	ON_COMMAND(IDM_OPENING, OnOpening)
	ON_COMMAND(IDM_CLOSING, OnClosing)
	ON_COMMAND(IDM_AVERRAGEFILTER3X3, OnAverrageFilter3x3)
	ON_COMMAND(IDM_AVERAGEFILTER5, OnAverageFilter5)
	ON_COMMAND(ID_IM_FFT, OnImFft)
	ON_COMMAND(ID_IM_ROTATE, OnImRotate)
	ON_COMMAND(ID_IM_TRANSLATE, OnImTranslate)
	ON_COMMAND(IDM_MEDIANFILTER3, OnMedianFilter3)
	ON_COMMAND(IDM_MEDIANFILTER5, OnMedianFilter5)
	ON_COMMAND(IDM_SOBELFILTERT_THICK, OnSobelFiltertThick)
	ON_COMMAND(IDM_SOBELFILTER_THIN, OnSobelFilterThin)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_COMMAND(IDM_THRESHOLD, OnThreshold)
	ON_WM_CANCELMODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoView construction/destruction

CDemoView::CDemoView()
{
	// TODO: add construction code here
	m_bDrawModelRect=FALSE;
	m_bDrawModelPos=FALSE;
	m_bDrawPMatchPos=FALSE;
	m_bDrawGMatchPos=FALSE;
	m_bDrawTempResult=FALSE;
}

CDemoView::~CDemoView()
{
	if(m_pDlgFeatMatch)delete m_pDlgFeatMatch;
}

BOOL CDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDemoView drawing

void CDemoView::OnDraw(CDC* pDC)
{
	CDemoDoc* pDoc = GetDocument();
	if (pDoc->flag)
	{
		MV_ID image= GetDocument()->image;
		
		
	 		SIZE sizeTotal;
	 		
			sizeTotal.cx = 1500;
	 		sizeTotal.cy = 1500;
			SetScrollSizes(MM_TEXT,sizeTotal);
	 		
		HDC hDC= pDC->GetSafeHdc(); 
		CRect rect; 
		rect.bottom = 1500;
		rect.left= 0;
		rect.top = 0;
		rect.right = 1500;
//		GetClientRect(&rect); 
		mvDispSelectWindow(image,hDC,&rect, TRUE);

		CPen YellowPen(PS_SOLID,3,RGB(255,255,0));
		CPen RedPen(PS_SOLID,3,RGB(255,0,0));
		CPen GreenPen(PS_SOLID,3,RGB(0,255,0));
		CPen BluePen(PS_SOLID,3,RGB(0,0,255));
		
		CPen* pOldPen;
		
		if(m_bDrawModelPos)
		{
			pOldPen=pDC->SelectObject(&RedPen);
//			DrawCross(pDC,m_pModel->GetPosX(),m_pModel->GetPosY());
		}
		
		if(m_bDrawPMatchPos)
		{
			pOldPen=pDC->SelectObject(&GreenPen);
//			DrawCross(pDC,m_pMatch->GetPosX(),m_pMatch->GetPosY());
		}
		
		if(m_bDrawGMatchPos)
		{
			pOldPen=pDC->SelectObject(&BluePen);
//			DrawCross(pDC,m_pFind->GetPosX(),m_pFind->GetPosY());
		}
		
		pOldPen=pDC->SelectObject(&YellowPen);
		
		if (m_bDrawModelRect)
			m_ModelRect.Draw(pDC);
		
		pDC->SelectObject(pOldPen);
	}

	if (m_bDrawTempResult)
	{
		
	}
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CDemoView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	m_pDoc = GetDocument();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);

	m_ModelRect.m_rect.SetRect(0,0,128,128);
	m_ModelRect.m_nStyle=CRectTracker::resizeInside|CRectTracker::dottedLine;

	m_pDlgFeatMatch = new CDlgFeatMatch(this);  //step four
	m_pDlgFeatMatch->Create();
	m_pDlgFeatMatch->ShowWindow(SW_HIDE);
	
}

/////////////////////////////////////////////////////////////////////////////
// CDemoView diagnostics

#ifdef _DEBUG
void CDemoView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CDemoView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CDemoDoc* CDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDemoDoc)));
	return (CDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDemoView message handlers

BOOL CDemoView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	
	if (pWnd == this && m_ModelRect.SetCursor(this, nHitTest)) 
		return TRUE; 
	return CScrollView::OnSetCursor(pWnd, nHitTest, message);
}

void CDemoView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int nIn; //define a click value
	nIn=m_ModelRect.HitTest(point); //locate cursor
	if(nIn>0)  //not in rectangular area£»
	{
		m_ModelRect.Track(this,point,TRUE);
		Invalidate();
      }
	CScrollView::OnLButtonDown(nFlags, point);
}


void CDemoView::OnFeatmatch() 
{
	// TODO: Add your command handler code here
	m_pDlgFeatMatch->ShowWindow(SW_SHOW);
	m_bDrawModelRect= TRUE;
	Invalidate();
}

void CDemoView::OnErosion() 
{
	// TODO: Add your command handler code here
	bool flag=mvImErosion(GetDocument()->image);
	if (false==flag) 
	{
		MessageBox("Binary image erosion error");
		return;
	}
	Invalidate();
}

void CDemoView::OnDilation() 
{
	// TODO: Add your command handler code here
	bool flag=mvImDilation(GetDocument()->image);
	if (false==flag) 
	{
		MessageBox("Binary image erosion error");
		return;
	}
	Invalidate();
}

void CDemoView::OnOpening() 
{
	// TODO: Add your command handler code here(image open operation, first erosion then dilation )
	bool flag=mvImOpening(GetDocument()->image);
	if (false==flag) 
	{
		MessageBox("Binary image open operation failed");
		return;
	}
	Invalidate();
}

void CDemoView::OnClosing() 
{
	// TODO: Add your command handler code here(image close operation, first dilation then erosion)
	bool flag=mvImClosing(GetDocument()->image);
	if (false==flag) 
	{
		MessageBox("Binary image close operation failed");
		return;
	}
	Invalidate();
}

void CDemoView::OnAverrageFilter3x3() 
{
	// TODO: Add your command handler code here
	bool flag=mvImAverageFilter(GetDocument()->image,MV_3X3);
	if (false==flag) 
	{
		MessageBox("Average Filter (3¡Á3)error");
		return;
	}
	Invalidate();
}

void CDemoView::OnAverageFilter5() 
{
	// TODO: Add your command handler code here
	bool flag=mvImAverageFilter(GetDocument()->image,MV_5X5);
	if (false==flag) 
	{
		MessageBox("Average Filter(5¡Á5) error");
		return;
	}
	Invalidate();
}

void CDemoView::OnImFft() 
{
	// TODO: Add your command handler code here
	MV_ID FFTImage=mvImFourier(GetDocument()->image);
	mvReleaseImage(GetDocument()->image);
	GetDocument()->image=FFTImage;
	Invalidate();
}

void CDemoView::OnImRotate() 
{
	// TODO: Add your command handler code here
	CDlgRotate dlg;
	if (dlg.DoModal()==IDOK)
	{
		mvImRotate(GetDocument()->image,dlg.angle,dlg.m_rotate_X,dlg.m_rotate_Y);
		Invalidate();
	}
}

void CDemoView::OnImTranslate() 
{
	// TODO: Add your command handler code here
	CDlgTranslate dlg;
	if (dlg.DoModal()==IDOK)
	{
		mvImTranslate(GetDocument()->image,dlg.m_translate_X,dlg.m_translate_Y);
		Invalidate();
	}
	
}

void CDemoView::OnMedianFilter3() 
{
	// TODO: Add your command handler code here
	bool flag=mvImMedianFilter(GetDocument()->image,MV_3X3);
	if (false==flag) 
	{
		MessageBox("Median Filter(3¡Á3) error");
		return;
	}
	Invalidate();
}

void CDemoView::OnMedianFilter5() 
{
	// TODO: Add your command handler code here
	bool flag=mvImMedianFilter(GetDocument()->image,MV_5X5);
	if (false==flag) 
	{
		MessageBox("Median Filter(5¡Á5) error");
		return;
	}
	Invalidate();
}

void CDemoView::OnSobelFiltertThick() 
{
	// TODO: Add your command handler code here
	mvImSobelEdge(GetDocument()->image,60,MV_THICK);
	Invalidate();
}

void CDemoView::OnSobelFilterThin() 
{
	// TODO: Add your command handler code here
	mvImSobelEdge(GetDocument()->image,60,MV_THIN);
	Invalidate();
}

void CDemoView::OnEditUndo() 
{
	// TODO: Add your command handler code here
	CString lastfilePath=GetDocument()->lastfilePath;
	if (!lastfilePath.IsEmpty())
	{
		GetDocument()->OnOpenDocument(lastfilePath.GetBuffer(lastfilePath.GetLength()));
	}
	Invalidate();
}

void CDemoView::OnThreshold() 
{
	// TODO: Add your command handler code here
	CDlgThreshold dlg;
	if (dlg.DoModal()==IDOK)
	{  
		long t;
		if (dlg.m_iterate==0)
		{
			t=MV_ITERATE;
		}
		if (dlg.m_iterate==1)
		{
			t=MV_OSTU;
		}
		if (dlg.m_iterate==2)
		{
			t=MV_MANUAL;
		}
		mvImBinarize(GetDocument()->image,t,&dlg.m_threshold);
		Invalidate();
	}
}


