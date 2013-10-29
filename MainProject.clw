; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CStartupBox
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MainProject.h"
LastPage=0

ClassCount=11
Class1=CMainProjectApp
Class2=CMainProjectDoc
Class3=CMainProjectView
Class4=CMainFrame

ResourceCount=5
Resource1=IDD_ABOUTBOX
Class5=CAboutDlg
Class6=CPicView
Class7=CData
Class8=CTeditView
Resource2=IDR_MAINFRAME
Resource3=IDR_TextToolBar
Class9=CChatView
Class10=CTalkChatCtrl
Resource4=IDR_PicViewToolBar
Class11=CStartupBox
Resource5=IDD_STARTUP_DIALOG

[CLS:CMainProjectApp]
Type=0
HeaderFile=MainProject.h
ImplementationFile=MainProject.cpp
Filter=N

[CLS:CMainProjectDoc]
Type=0
HeaderFile=MainProjectDoc.h
ImplementationFile=MainProjectDoc.cpp
Filter=N
LastObject=ID_TEXTFILE_OPEN
BaseClass=CDocument
VirtualFilter=DC

[CLS:CMainProjectView]
Type=0
HeaderFile=MainProjectView.h
ImplementationFile=MainProjectView.cpp
Filter=C
LastObject=CMainProjectView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_STARTUP
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=MainProject.cpp
ImplementationFile=MainProject.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_STARTUP
Command2=ID_TEXTFILE_OPEN
Command3=ID_APP_ABOUT
CommandCount=3

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
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

[CLS:CPicView]
Type=0
HeaderFile=PicView.h
ImplementationFile=PicView.cpp
BaseClass=CView
Filter=C
VirtualFilter=VWC
LastObject=CPicView

[CLS:CData]
Type=0
HeaderFile=Data.h
ImplementationFile=Data.cpp
BaseClass=CAsyncSocket
Filter=W
LastObject=CData

[CLS:CTeditView]
Type=0
HeaderFile=TeditView.h
ImplementationFile=TeditView.cpp
BaseClass=CView
Filter=C
LastObject=ID_EDIT_CUT
VirtualFilter=VWC

[TB:IDR_TextToolBar]
Type=1
Class=CTeditView
Command1=ID_TEXTFILE_NEW
Command2=ID_TEXTFILE_OPEN
Command3=ID_TEXTFILE_SAVE
Command4=ID_TEXTFILE_PRINT
CommandCount=4

[TB:IDR_PicViewToolBar]
Type=1
Class=CPicView
Command1=ID_PICFILE_NEW
Command2=ID_PICFILE_OPEN
Command3=ID_PICFILE_SAVE
Command4=ID_PICFILE_PRINT
Command5=ID_BUTTON_BLACKPEN
Command6=ID_BUTTON_ERASE
CommandCount=6

[CLS:CChatView]
Type=0
HeaderFile=ChatView.h
ImplementationFile=ChatView.cpp
BaseClass=CRichEditView
Filter=W
LastObject=CChatView
VirtualFilter=VWC

[CLS:CTalkChatCtrl]
Type=0
HeaderFile=TalkChatCtrl.h
ImplementationFile=TalkChatCtrl.cpp
BaseClass=CRichEditCtrl
Filter=W
VirtualFilter=WC
LastObject=CTalkChatCtrl

[DLG:IDD_STARTUP_DIALOG]
Type=1
Class=CStartupBox
ControlCount=9
Control1=IDC_RADIOSERVER,button,1342308361
Control2=IDC_RADIOCLIENT,button,1342177289
Control3=IDC_OK,button,1342242816
Control4=IDC_CANCEL,button,1342242816
Control5=IDC_IP_ADDRESS,edit,1484849280
Control6=IDC_PORT_NO,edit,1484849280
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,button,1342177287
Control9=IDC_STATIC,static,1342308352

[CLS:CStartupBox]
Type=0
HeaderFile=StartupBox.h
ImplementationFile=StartupBox.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_PORT_NO
VirtualFilter=dWC

