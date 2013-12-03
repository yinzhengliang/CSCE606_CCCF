; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDemoView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "demo.h"
LastPage=0

ClassCount=9
Class1=CDemoApp
Class2=CAboutDlg
Class3=CDemoDoc
Class4=CDemoView
Class5=CDlgCal
Class6=CDlgFeatMatch
Class7=CDlgTemp
Class8=CMainFrame

ResourceCount=14
Resource1=IDD_ABOUTBOX
Resource2=IDD_DLG_IMHIST (English (U.S.))
Resource3=IDD_DLG_IMROTATE (English (U.S.))
Resource4=IDD_DLG_IM_TRANSLATE (English (U.S.))
Resource5=IDR_MAINFRAME (English (U.S.))
Resource6=IDD_DLG_IMLINTRANS (English (U.S.))
Resource7=IDR_MAINFRAME
Resource8=IDD_FEAT_MATCH (English (U.S.))
Class9=CDlgThreshold
Resource9=IDD_ABOUTBOX (English (U.S.))
Resource10=IDD_THRESHOLD (English (U.S.))
Resource11=IDD_FEAT_MATCH
Resource12=IDD_DLG_IMROTATE
Resource13=IDD_THRESHOLD
Resource14=IDD_DLG_IM_TRANSLATE

[CLS:CDemoApp]
Type=0
BaseClass=CWinApp
HeaderFile=Demo.h
ImplementationFile=Demo.cpp
Filter=N
VirtualFilter=AC

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=Demo.cpp
ImplementationFile=Demo.cpp
LastObject=ID_APP_ABOUT
Filter=D
VirtualFilter=dWC

[CLS:CDemoDoc]
Type=0
BaseClass=CDocument
HeaderFile=DemoDoc.h
ImplementationFile=DemoDoc.cpp

[CLS:CDemoView]
Type=0
BaseClass=CScrollView
HeaderFile=DemoView.h
ImplementationFile=DemoView.cpp
Filter=C
VirtualFilter=VWC
LastObject=IDM_SOBELFILTERT_THICK

[CLS:CDlgCal]
Type=0
BaseClass=CDialog
HeaderFile=DlgCal.h
ImplementationFile=DlgCal.cpp

[CLS:CDlgFeatMatch]
Type=0
BaseClass=CDialog
HeaderFile=DlgFeatMatch.h
ImplementationFile=DlgFeatMatch.cpp
Filter=D
VirtualFilter=dWC
LastObject=CDlgFeatMatch

[CLS:CDlgTemp]
Type=0
BaseClass=CDialog
HeaderFile=DlgTemp.h
ImplementationFile=DlgTemp.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT_ACCEPTANCE

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[CLS:CDlgThreshold]
Type=0
HeaderFile=DlgThreshold.h
ImplementationFile=DlgThreshold.cpp
BaseClass=CDialog
Filter=D
LastObject=IDOK
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DLG_IMHIST (English (U.S.))]
Type=1
Class=?
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_STATIC_CHART,static,1342181382

[DLG:IDD_DLG_IMLINTRANS (English (U.S.))]
Type=1
Class=?
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDC_STATIC_CHART,static,1342181382
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,button,1342177287
Control6=IDC_LINTRANS_A,edit,1350631552
Control7=IDC_LINTRANS_B,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDCANCEL,button,1342242816

[DLG:IDD_FEAT_MATCH (English (U.S.))]
Type=1
Class=CDlgFeatMatch
ControlCount=45
Control1=IDC_MODELIMAGE,static,1342177287
Control2=IDC_LOCATEMODEL,button,1342242816
Control3=IDC_STATIC,static,1342177287
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,button,1342177287
Control7=IDC_STATIC,button,1342177287
Control8=IDC_MODELX,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_MODELY,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_MODELWIDTH,edit,1350631552
Control13=IDC_MODELLENGHT,edit,1350631552
Control14=IDC_GRAYFACTOR,edit,1350631552
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_WHOLEIMAGE,button,1342242819
Control19=IDC_TROIX,edit,1350631552
Control20=IDC_TROIY,edit,1350631552
Control21=IDC_TROIWIDTH,edit,1350631552
Control22=IDC_TROILENGTH,edit,1350631552
Control23=IDC_LOCATEROI,button,1342242816
Control24=IDC_WHOLETARGET,button,1342242819
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC,static,1342308352
Control28=IDC_STATIC,static,1342308352
Control29=IDC_TRAIN,button,1342242816
Control30=IDC_MATCHSINGLE,button,1342242816
Control31=IDC_MATCHMULTI,button,1342242816
Control32=IDOK,button,1342242816
Control33=IDC_POSX,edit,1350631552
Control34=IDC_POSY,edit,1350631552
Control35=IDC_TIME,edit,1350631552
Control36=IDC_STATIC,static,1342308352
Control37=IDC_STATIC,static,1342308352
Control38=IDC_STATIC,static,1342308352
Control39=IDC_SCORE1,edit,1350631552
Control40=IDC_STATIC,static,1342308352
Control41=IDC_ACCEPTANCE,edit,1350631552
Control42=IDC_STATIC,static,1342308352
Control43=IDC_STATIC,static,1342308352
Control44=IDC_LoadModel,button,1342242816
Control45=IDC_SaveModel,button,1342242816

[DLG:IDD_DLG_IMROTATE (English (U.S.))]
Type=1
Class=?
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_ROTATE_DEG,button,1342308361
Control5=IDC_ROTATE_RAD,button,1342177289
Control6=IDC_ROTATE_ANGLE,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_ROTATE_X,edit,1350631552
Control9=IDC_ROTATE_Y,edit,1350631552
Control10=IDC_STATIC,button,1342177287
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352

[DLG:IDD_DLG_IM_TRANSLATE (English (U.S.))]
Type=1
Class=?
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_TRANSLATE_X,edit,1350631552
Control5=IDC_TRANSLATE_Y,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CDemoView
Command1=ID_FILE_OPEN
Command2=IDM_OPENFOLDER
Command3=ID_APP_EXIT
Command4=IDM_EROSION
Command5=IDM_DILATION
Command6=IDM_OPENING
Command7=IDM_CLOSING
Command8=IDM_AVERRAGEFILTER3X3
Command9=IDM_AVERAGEFILTER5
Command10=IDM_MEDIANFILTER3
Command11=IDM_MEDIANFILTER5
Command12=IDM_SOBELFILTERT_THICK
Command13=IDM_SOBELFILTER_THIN
Command14=ID_IM_LINTRANS
Command15=ID_IM_HIST
Command16=ID_IM_TRANSLATE
Command17=ID_IM_ROTATE
Command18=ID_IM_FFT
Command19=IDM_THRESHOLD
Command20=ID_BLOB_AREA
Command21=ID_APP_ABOUT
CommandCount=21

[DLG:IDD_THRESHOLD (English (U.S.))]
Type=1
Class=CDlgThreshold
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_ITERATE,button,1342308361
Control5=IDC_OSTU,button,1342177289
Control6=IDC_MANUAL,button,1342177289
Control7=IDC_THRESHOLD,edit,1350631552
Control8=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CDemoView
Command1=ID_FILE_OPEN
Command2=IDM_OPENFOLDER
Command3=ID_APP_EXIT
Command4=ID_IM_TRANSLATE
Command5=ID_IM_ROTATE
Command6=IDM_AVERRAGEFILTER3X3
Command7=IDM_AVERAGEFILTER5
Command8=IDM_MEDIANFILTER3
Command9=IDM_MEDIANFILTER5
Command10=IDM_SOBELFILTERT_THICK
Command11=IDM_SOBELFILTER_THIN
Command12=IDM_THRESHOLD
Command13=IDM_EROSION
Command14=IDM_DILATION
Command15=IDM_OPENING
Command16=IDM_CLOSING
Command17=ID_IM_FFT
Command18=ID_APP_ABOUT
CommandCount=18

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_FEAT_MATCH]
Type=1
Class=?
ControlCount=45
Control1=IDC_MODELIMAGE,static,1342177287
Control2=IDC_LOCATEMODEL,button,1342242816
Control3=IDC_STATIC,static,1342177287
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,button,1342177287
Control7=IDC_STATIC,button,1342177287
Control8=IDC_MODELX,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_MODELY,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_MODELWIDTH,edit,1350631552
Control13=IDC_MODELLENGHT,edit,1350631552
Control14=IDC_GRAYFACTOR,edit,1350631552
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_WHOLEIMAGE,button,1342242819
Control19=IDC_TROIX,edit,1350631552
Control20=IDC_TROIY,edit,1350631552
Control21=IDC_TROIWIDTH,edit,1350631552
Control22=IDC_TROILENGTH,edit,1350631552
Control23=IDC_LOCATEROI,button,1342242816
Control24=IDC_WHOLETARGET,button,1342242819
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC,static,1342308352
Control28=IDC_STATIC,static,1342308352
Control29=IDC_TRAIN,button,1342242816
Control30=IDC_MATCHSINGLE,button,1342242816
Control31=IDC_MATCHMULTI,button,1342242816
Control32=IDOK,button,1342242816
Control33=IDC_POSX,edit,1350631552
Control34=IDC_POSY,edit,1350631552
Control35=IDC_TIME,edit,1350631552
Control36=IDC_STATIC,static,1342308352
Control37=IDC_STATIC,static,1342308352
Control38=IDC_STATIC,static,1342308352
Control39=IDC_SCORE1,edit,1350631552
Control40=IDC_STATIC,static,1342308352
Control41=IDC_ACCEPTANCE,edit,1350631552
Control42=IDC_STATIC,static,1342308352
Control43=IDC_STATIC,static,1342308352
Control44=IDC_LoadModel,button,1342242816
Control45=IDC_SaveModel,button,1342242816

[DLG:IDD_DLG_IMROTATE]
Type=1
Class=?
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_ROTATE_DEG,button,1342308361
Control5=IDC_ROTATE_RAD,button,1342177289
Control6=IDC_ROTATE_ANGLE,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_ROTATE_X,edit,1350631552
Control9=IDC_ROTATE_Y,edit,1350631552
Control10=IDC_STATIC,button,1342177287
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352

[DLG:IDD_THRESHOLD]
Type=1
Class=?
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_ITERATE,button,1342308361
Control5=IDC_OSTU,button,1342177289
Control6=IDC_MANUAL,button,1342177289
Control7=IDC_THRESHOLD,edit,1350631552
Control8=IDC_STATIC,static,1342308352

[DLG:IDD_DLG_IM_TRANSLATE]
Type=1
Class=?
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_TRANSLATE_X,edit,1350631552
Control5=IDC_TRANSLATE_Y,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352

