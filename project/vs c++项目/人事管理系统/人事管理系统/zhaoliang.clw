; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CLoginDlg
LastTemplate=CFormView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "zhaoliang.h"
LastPage=0

ClassCount=10
Class1=CzhaoliangApp
Class3=CMainFrame
Class4=CChildFrame

ResourceCount=7
Resource1=IDD_ABOUTBOX
Resource2=IDR_PERSONTYPE
Resource3=IDD_FORMVIEW_ADD
Class2=CChildView
Class5=CAboutDlg
Class6=CLoginDlg
Resource4=IDR_MAINFRAME
Class7=CTheChildFrame
Class8=CAddView
Resource5=IDD_DLG_LOGIN
Class9=CChangeView
Resource6=IDD_FORMVIEW_CHANGE
Class10=CSearchView
Resource7=IDD_FORMVIEW_SEARCH

[CLS:CzhaoliangApp]
Type=0
HeaderFile=zhaoliang.h
ImplementationFile=zhaoliang.cpp
Filter=N
LastObject=CzhaoliangApp

[CLS:CChildView]
Type=0
HeaderFile=ChildView.h
ImplementationFile=ChildView.cpp
Filter=N

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CMDIFrameWnd
VirtualFilter=fWC
LastObject=ID_MANAGER_CHANGE


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M


[CLS:CAboutDlg]
Type=0
HeaderFile=zhaoliang.cpp
ImplementationFile=zhaoliang.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177294
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,button,1342177287

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_SYSTEM_CONNECT
Command2=ID_SYSTEM_DISCONNECT
Command3=ID_APP_EXIT
Command4=ID_MANAGE_ADD
Command5=ID_MANAGER_CHANGE
Command6=ID_MANAGER_SEARCH
Command7=ID_WINDOW_CASCADE
Command8=ID_WINDOW_TILE_HORZ
Command9=ID_WINDOW_TILE_VERT
Command10=ID_WINDOW_MINIALL
Command11=ID_APP_ABOUT
CommandCount=11

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_SYSTEM_CONNECT
Command2=ID_SYSTEM_DISCONNECT
Command3=ID_MANAGE_ADD
Command4=ID_MANAGER_CHANGE
Command5=ID_MANAGER_SEARCH
Command6=ID_WINDOW_CASCADE
Command7=ID_WINDOW_TILE_HORZ
Command8=ID_WINDOW_TILE_VERT
Command9=ID_APP_ABOUT
CommandCount=9

[MNU:IDR_PERSONTYPE]
Type=1
Class=CzhaoliangView
Command1=ID_FILE_NEW
Command2=ID_FILE_CLOSE
Command3=ID_APP_EXIT
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_VIEW_TOOLBAR
Command9=ID_VIEW_STATUS_BAR
Command10=ID_WINDOW_CASCADE
Command11=ID_WINDOW_TILE_HORZ
Command12=ID_WINDOW_ARRANGE
Command13=ID_APP_ABOUT
CommandCount=13

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_APP_EXIT
Command4=ID_EDIT_PASTE
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_APP_ABOUT
Command8=ID_SYSTEM_CONNECT
Command9=ID_SYSTEM_DISCONNECT
Command10=ID_NEXT_PANE
Command11=ID_PREV_PANE
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_EDIT_CUT
Command15=ID_EDIT_UNDO
CommandCount=15

[DLG:IDD_DLG_LOGIN]
Type=1
Class=CLoginDlg
ControlCount=9
Control1=IDC_EDT_USER,edit,1350631552
Control2=IDC_EDT_PASSWD,edit,1350631584
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_STATIC_LOGINTEXT,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_CMD_DSN,combobox,1344340226
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352

[CLS:CLoginDlg]
Type=0
HeaderFile=LoginDlg.h
ImplementationFile=LoginDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDT_USER
VirtualFilter=dWC

[CLS:CAddView]
Type=0
HeaderFile=AddView.h
ImplementationFile=AddView.cpp
BaseClass=CFormView
Filter=D
LastObject=CAddView
VirtualFilter=VWC

[CLS:CTheChildFrame]
Type=0
HeaderFile=TheChildFrame.h
ImplementationFile=TheChildFrame.cpp
BaseClass=CMDIChildWnd
Filter=M
LastObject=CTheChildFrame
VirtualFilter=mfWC

[DLG:IDD_FORMVIEW_ADD]
Type=1
Class=CAddView
ControlCount=28
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_ADD_EDT_ID,edit,1484849280
Control9=IDC_STATIC,static,1342308352
Control10=IDC_ADD_EDT_PASSWD,edit,1484849280
Control11=IDC_ADD_EDT_NAME,edit,1350631552
Control12=IDC_ADD_RADIO_MALE,button,1342177289
Control13=IDC_ADD_RADIO_FEMALE,button,1342177289
Control14=IDC_ADD_EDT_BIRTHDAY,edit,1350631552
Control15=IDC_ADD_CMB_DEPARTMENT,combobox,1344339971
Control16=IDC_ADD_CMB_JOB,combobox,1344339971
Control17=IDC_ADD_CMB_EDULEVEL,combobox,1344339971
Control18=IDC_STATIC,static,1342308352
Control19=IDC_ADD_EDT_SPECIALTY,edit,1350631552
Control20=IDC_STATIC,static,1342308352
Control21=IDC_ADD_EDT_ADDRESS,edit,1350631552
Control22=IDC_STATIC,static,1342308352
Control23=IDC_ADD_EDT_TEL,edit,1350631552
Control24=IDC_STATIC,static,1342308352
Control25=IDC_ADD_EDT_EMAIL,edit,1350631552
Control26=IDC_STATIC,static,1342308352
Control27=IDC_ADD_EDT_MEMO,edit,1350631556
Control28=IDC_ADD_BTN_ADD,button,1342242816

[DLG:IDD_FORMVIEW_CHANGE]
Type=1
Class=CChangeView
ControlCount=17
Control1=IDC_STATIC,static,1342308352
Control2=IDC_CHANGE_EDT_ID,edit,1350631552
Control3=IDC_STATIC,button,1342177287
Control4=IDC_CHANGE_RADIO_JOB,button,1342177289
Control5=IDC_CHANGE_RADIO_FIRE,button,1342177289
Control6=IDC_STATIC,static,1342308352
Control7=IDC_CHANGE_DATETIMEPICKER,SysDateTimePick32,1342242848
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_CHANGE_EDT_NAME,edit,1484849280
Control12=IDC_CHANGE_CMB_DEPARTMENT,combobox,1344339971
Control13=IDC_CHANGE_CMB_JOB,combobox,1344339971
Control14=IDC_STATIC,button,1342177287
Control15=IDC_STATIC,static,1342308352
Control16=IDC_CHANGE_EDT_DESCRIPTION,edit,1350631556
Control17=IDC_CHANGE_BTN_CHANGE,button,1342242816

[CLS:CChangeView]
Type=0
HeaderFile=ChangeView.h
ImplementationFile=ChangeView.cpp
BaseClass=CFormView
Filter=D
LastObject=CChangeView
VirtualFilter=VWC

[DLG:IDD_FORMVIEW_SEARCH]
Type=1
Class=CSearchView
ControlCount=31
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_SEARCH_EDT_ID,edit,1350631552
Control9=IDC_SEARCH_EDT_PASSWD,edit,1350631552
Control10=IDC_STATIC,static,1342308352
Control11=IDC_SEARCH_RADIO_MALE,button,1342177289
Control12=IDC_SEARCH_EDT_NAME,edit,1350631552
Control13=IDC_SEARCH_RADIO_FEMALE,button,1342177289
Control14=IDC_SEARCH_EDT_BIRTHDAY,edit,1350631552
Control15=IDC_SEARCH_CMB_DEPARTMENT,combobox,1344339971
Control16=IDC_SEARCH_CMB_JOB,combobox,1344339971
Control17=IDC_SEARCH_CMB_EDULEVEL,combobox,1344339971
Control18=IDC_STATIC,static,1342308352
Control19=IDC_SEARCH_EDT_SPECIALTY,edit,1350631552
Control20=IDC_STATIC,static,1342308352
Control21=IDC_SEARCH_EDT_ADDRESS,edit,1350631552
Control22=IDC_STATIC,static,1342308352
Control23=IDC_SEARCH_EDT_TEL,edit,1350631552
Control24=IDC_STATIC,static,1342308352
Control25=IDC_SEARCH_EDT_EMAIL,edit,1350631552
Control26=IDC_STATIC,static,1342308352
Control27=IDC_SEARCH_EDT_MEMO,edit,1350631556
Control28=IDC_SEARCH_BTN_CHANGE,button,1342242816
Control29=IDC_SEARCH_BTN_CHGPASSWD,button,1342242816
Control30=IDC_SEARCH_LIST,SysListView32,1350631425
Control31=IDC_STATIC,static,1342308352

[CLS:CSearchView]
Type=0
HeaderFile=SearchView.h
ImplementationFile=SearchView.cpp
BaseClass=CFormView
Filter=D
LastObject=CSearchView
VirtualFilter=VWC

