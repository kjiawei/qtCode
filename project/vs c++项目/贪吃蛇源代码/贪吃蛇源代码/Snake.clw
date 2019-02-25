; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CChangeSpeedDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "snake.h"
LastPage=0

ClassCount=7
Class1=CAboutDlg
Class2=CMainFrame
Class3=CSnakeApp
Class4=CSnakeDoc
Class5=CSnakeView

ResourceCount=4
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Class6=CScoreBoardDlg
Resource3=IDD_SCOREBOARD
Class7=CChangeSpeedDlg
Resource4=IDD_CHANGESPEEDDLG

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=AboutDlg.h
ImplementationFile=AboutDlg.cpp
LastObject=CAboutDlg

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=W
VirtualFilter=fWC
LastObject=CMainFrame

[CLS:CSnakeApp]
Type=0
BaseClass=CWinApp
HeaderFile=Snake.h
ImplementationFile=Snake.cpp
Filter=N
VirtualFilter=AC
LastObject=CSnakeApp

[CLS:CSnakeDoc]
Type=0
BaseClass=CDocument
HeaderFile=SnakeDoc.h
ImplementationFile=SnakeDoc.cpp

[CLS:CSnakeView]
Type=0
BaseClass=CView
HeaderFile=SnakeView.h
ImplementationFile=SnakeView.cpp
LastObject=CSnakeView
Filter=W
VirtualFilter=VWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

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

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=IDM_CHANGELEVEL
Command2=ID_APP_ABOUT
Command3=ID_APP_EXIT
CommandCount=3

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_SCOREBOARD]
Type=1
Class=CScoreBoardDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1073807360
Control3=IDC_EDIT_SCORES,edit,1350633668

[CLS:CScoreBoardDlg]
Type=0
HeaderFile=ScoreBoardDlg.h
ImplementationFile=ScoreBoardDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CScoreBoardDlg
VirtualFilter=dWC

[DLG:IDD_CHANGESPEEDDLG]
Type=1
Class=CChangeSpeedDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_SPEED,edit,1350631552
Control5=IDC_SPIN,msctls_updown32,1342177330

[CLS:CChangeSpeedDlg]
Type=0
HeaderFile=ChangeSpeedDlg.h
ImplementationFile=ChangeSpeedDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

