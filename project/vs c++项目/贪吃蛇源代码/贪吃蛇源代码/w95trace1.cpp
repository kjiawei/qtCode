
/*
    Implementation of Win95 tracing facility to mimic that of NT
*/

#include "stdafx.h"

#include "windows.h"
#include <stdio.h>
#include <stdarg.h>
#include <process.h>
//#include "w95trace.h"
#include <afxpriv.h>	// for MFC WM_ messages


#ifdef _DEBUG

int CTraceFn::nIndent=-1;	    // current indent level
#define _countof(array) (sizeof(array)/sizeof(array[0]))

#include <time.h>
void ClearDebugWindow(char *str/*=0*/, BOOL bClean/*=TRUE*/)
{
    char timestr[80];
    time_t ltime;
    time(&ltime);
    wsprintf(timestr, "********** %s **********", ctime(&ltime));

    if ((bClean == FALSE) && (str == 0)) return;
    else 
    {
        HWND hDbgWnd, hEdit;
        hDbgWnd = (HWND) FindWindow("DBWin32", "Debug Messages (WIN32)");
        if (hDbgWnd != NULL)
        {
            char *fullStr = 0;
            if (str == 0)
            {
                fullStr = new char[60];
                strcpy(fullStr, "\r\n");
                strcat(fullStr, timestr);
                strcat(fullStr, "\r\n\r\n");
            }
            else
            {
                fullStr = new char[strlen(str)+1+120];
                strcpy(fullStr, "\r\n");
                strcat(fullStr, timestr);
                strcat(fullStr, "\r\n");
                strcat(fullStr, str);
                strcat(fullStr, "\r\n\r\n");
            }
            hEdit = (HWND) FindWindowEx(hDbgWnd, NULL, "Edit", "");
            int len;
            if ((bClean == FALSE) && (str != 0))
            {
                len = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
                SendMessage(hEdit, EM_SETSEL, len+1, len+1);
                SendMessage(hEdit, EM_REPLACESEL, FALSE, (long) fullStr);
            }
            else // (bClean == TRUE)
                SendMessage(hEdit, WM_SETTEXT, 0, (long) fullStr);
            len = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
            SendMessage(hEdit, EM_SETSEL, len+1, len+1);
            delete[] fullStr;
        }
    }
}

void OutputDebugStringW95( LPCTSTR lpOutputString, ...)
{

    HANDLE heventDBWIN;  /* DBWIN32 synchronization object */
    HANDLE heventData;   /* data passing synch object */
    HANDLE hSharedFile;  /* memory mapped file shared data */
    LPSTR lpszSharedMem;
    int iWC;
    char achBuffer1[256];
    char achBuffer[256];

    /* create the output buffer */
    va_list args;
    va_start(args, lpOutputString);
    iWC = vsprintf(achBuffer1, lpOutputString, args);
    if (iWC >= 256) 
        vsprintf(achBuffer1, "%s", "Insufficient memory allocation in OutputDebugStrW95()\n");
    va_end(args);

    /* insert spaces for TRACEFN */
	static BOOL bStartNewLine = TRUE;
	char* nextline;
    iWC = 0;
    for (char* start=achBuffer1; *start; start=nextline+1) 
    {
		if (bStartNewLine) 
        {
			if ((afxTraceFlags & traceMultiApp) && (AfxGetApp() != NULL))
				iWC+=sprintf(&achBuffer[iWC], "%s: ", AfxGetApp()->m_pszExeName);
            for (int i=0; i<CTraceFn::nIndent; i++)
			    achBuffer[iWC++] = ' ';
            if (CTraceFn::nIndent>0) 
                achBuffer[iWC] = '\0';
			bStartNewLine = FALSE;
		}
		nextline = strchr(start, '\n');
		if (nextline) {
			*nextline = 0; // terminate string at newline
			bStartNewLine = TRUE;
		}
        iWC+=sprintf(&achBuffer[iWC], start);
		if (!nextline)
			break;
        iWC+=sprintf(&achBuffer[iWC], "\n");
	}

    /* 
        Do a regular OutputDebugString so that the output is 
        still seen in the debugger window if it exists.

        This ifdef is necessary to avoid infinite recursion 
        from the inclusion of W95TRACE.H
    */
#ifdef _UNICODE
    ::OutputDebugStringW(achBuffer);
#else
    ::OutputDebugStringA(achBuffer);
#endif

    /* bail if it's not Win95 */
    {
        OSVERSIONINFO VerInfo;
        VerInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
        GetVersionEx(&VerInfo);
        if ( VerInfo.dwPlatformId != VER_PLATFORM_WIN32_WINDOWS )
            return;
    }

    /* make sure DBWIN is open and waiting */
    heventDBWIN = OpenEvent(EVENT_MODIFY_STATE, FALSE, "DBWIN_BUFFER_READY");
    if ( !heventDBWIN )
    {
        //MessageBox(NULL, "DBWIN_BUFFER_READY nonexistent", NULL, MB_OK);
        return;            
    }

    /* get a handle to the data synch object */
    heventData = OpenEvent(EVENT_MODIFY_STATE, FALSE, "DBWIN_DATA_READY");
    if ( !heventData )
    {
        // MessageBox(NULL, "DBWIN_DATA_READY nonexistent", NULL, MB_OK);
        CloseHandle(heventDBWIN);
        return;            
    }
    
    hSharedFile = CreateFileMapping((HANDLE)-1, NULL, PAGE_READWRITE, 0, 4096, "DBWIN_BUFFER");
    if (!hSharedFile) 
    {
        //MessageBox(NULL, "DebugTrace: Unable to create file mapping object DBWIN_BUFFER", "Error", MB_OK);
        CloseHandle(heventDBWIN);
        CloseHandle(heventData);
        return;
    }

    lpszSharedMem = (LPSTR)MapViewOfFile(hSharedFile, FILE_MAP_WRITE, 0, 0, 512);
    if (!lpszSharedMem) 
    {
        //MessageBox(NULL, "DebugTrace: Unable to map shared memory", "Error", MB_OK);
        CloseHandle(heventDBWIN);
        CloseHandle(heventData);
        return;
    }

    /* wait for buffer event */
    WaitForSingleObject(heventDBWIN, INFINITE);

    /* write it to the shared memory */
    *((LPDWORD)lpszSharedMem) = _getpid();
    wsprintf(lpszSharedMem + sizeof(DWORD), "%s", achBuffer);

    /* signal data ready event */
    SetEvent(heventData);

    /* clean up handles */
    CloseHandle(hSharedFile);
    CloseHandle(heventData);
    CloseHandle(heventDBWIN);

    return;
}

//////////////////
// Get window name in the form classname[HWND,title]
// Searches all the parents for a window with a title.
//
CString sDbgName(CWnd* pWnd)
{
	CString sTitle;
	HWND hwnd = pWnd->GetSafeHwnd();
	if (hwnd==NULL)
		sTitle = "NULL";
	else if (!::IsWindow(hwnd))
		sTitle = "[bad window]";
	else {
		sTitle = "[no title]";
		for (CWnd* pw = pWnd; pw; pw = pw->GetParent()) {
			if (pw->GetWindowTextLength() > 0) {
				pw->GetWindowText(sTitle);
				break;
			}
		}
	}
	CString s;
	s.Format("%s[0x%04x,\"%s\"]", 
		pWnd ? pWnd->GetRuntimeClass()->m_lpszClassName : "NULL",
		hwnd, (LPCTSTR)sTitle);
	return s;
}

struct {
	UINT		msg;
	LPCTSTR	name;
} MsgData[] = {
	{ WM_CREATE,_T("WM_CREATE") },
	{ WM_DESTROY,_T("WM_DESTROY") },
	{ WM_MOVE,_T("WM_MOVE") },
	{ WM_SIZE,_T("WM_SIZE") },
	{ WM_ACTIVATE,_T("WM_ACTIVATE") },
	{ WM_SETFOCUS,_T("WM_SETFOCUS") },
	{ WM_KILLFOCUS,_T("WM_KILLFOCUS") },
	{ WM_ENABLE,_T("WM_ENABLE") },
	{ WM_SETREDRAW,_T("WM_SETREDRAW") },
	{ WM_SETTEXT,_T("WM_SETTEXT") },
	{ WM_GETTEXT,_T("WM_GETTEXT") },
	{ WM_GETTEXTLENGTH,_T("WM_GETTEXTLENGTH") },
	{ WM_PAINT,_T("WM_PAINT") },
	{ WM_CLOSE,_T("WM_CLOSE") },
	{ WM_QUERYENDSESSION,_T("WM_QUERYENDSESSION") },
	{ WM_QUIT,_T("WM_QUIT") },
	{ WM_QUERYOPEN,_T("WM_QUERYOPEN") },
	{ WM_ERASEBKGND,_T("WM_ERASEBKGND") },
	{ WM_SYSCOLORCHANGE,_T("WM_SYSCOLORCHANGE") },
	{ WM_ENDSESSION,_T("WM_ENDSESSION") },
	{ WM_SHOWWINDOW,_T("WM_SHOWWINDOW") },
	{ WM_WININICHANGE,_T("WM_WININICHANGE") },
	{ WM_SETTINGCHANGE,_T("WM_SETTINGCHANGE") },
	{ WM_DEVMODECHANGE,_T("WM_DEVMODECHANGE") },
	{ WM_ACTIVATEAPP,_T("WM_ACTIVATEAPP") },
	{ WM_FONTCHANGE,_T("WM_FONTCHANGE") },
	{ WM_TIMECHANGE,_T("WM_TIMECHANGE") },
	{ WM_CANCELMODE,_T("WM_CANCELMODE") },
	{ WM_SETCURSOR,_T("WM_SETCURSOR") },
	{ WM_MOUSEACTIVATE,_T("WM_MOUSEACTIVATE") },
	{ WM_CHILDACTIVATE,_T("WM_CHILDACTIVATE") },
	{ WM_QUEUESYNC,_T("WM_QUEUESYNC") },
	{ WM_GETMINMAXINFO,_T("WM_GETMINMAXINFO") },
	{ WM_PAINTICON,_T("WM_PAINTICON") },
	{ WM_ICONERASEBKGND,_T("WM_ICONERASEBKGND") },
	{ WM_NEXTDLGCTL,_T("WM_NEXTDLGCTL") },
	{ WM_SPOOLERSTATUS,_T("WM_SPOOLERSTATUS") },
	{ WM_DRAWITEM,_T("WM_DRAWITEM") },
	{ WM_MEASUREITEM,_T("WM_MEASUREITEM") },
	{ WM_DELETEITEM,_T("WM_DELETEITEM") },
	{ WM_VKEYTOITEM,_T("WM_VKEYTOITEM") },
	{ WM_CHARTOITEM,_T("WM_CHARTOITEM") },
	{ WM_SETFONT,_T("WM_SETFONT") },
	{ WM_GETFONT,_T("WM_GETFONT") },
	{ WM_SETHOTKEY,_T("WM_SETHOTKEY") },
	{ WM_GETHOTKEY,_T("WM_GETHOTKEY") },
	{ WM_QUERYDRAGICON,_T("WM_QUERYDRAGICON") },
	{ WM_COMPAREITEM,_T("WM_COMPAREITEM") },
	{ WM_COMPACTING,_T("WM_COMPACTING") },
	{ WM_COMMNOTIFY,_T("WM_COMMNOTIFY") },
	{ WM_WINDOWPOSCHANGING,_T("WM_WINDOWPOSCHANGING") },
	{ WM_WINDOWPOSCHANGED,_T("WM_WINDOWPOSCHANGED") },
	{ WM_POWER,_T("WM_POWER") },
	{ WM_COPYDATA,_T("WM_COPYDATA") },
	{ WM_CANCELJOURNAL,_T("WM_CANCELJOURNAL") },
#if(WINVER >= 0x0400)
	{ WM_NOTIFY,_T("WM_NOTIFY") },
	{ WM_INPUTLANGCHANGEREQUEST,_T("WM_INPUTLANGCHANGEREQUEST") },
	{ WM_INPUTLANGCHANGE,_T("WM_INPUTLANGCHANGE") },
	{ WM_TCARD,_T("WM_TCARD") },
	{ WM_HELP,_T("WM_HELP") },
	{ WM_USERCHANGED,_T("WM_USERCHANGED") },
	{ WM_NOTIFYFORMAT,_T("WM_NOTIFYFORMAT") },
	{ WM_CONTEXTMENU,_T("WM_CONTEXTMENU") },
	{ WM_STYLECHANGING,_T("WM_STYLECHANGING") },
	{ WM_STYLECHANGED,_T("WM_STYLECHANGED") },
	{ WM_DISPLAYCHANGE,_T("WM_DISPLAYCHANGE") },
	{ WM_GETICON,_T("WM_GETICON") },
	{ WM_SETICON,_T("WM_SETICON") },
#endif /* WINVER >= 0x0400 */
	{ WM_NCCREATE,_T("WM_NCCREATE") },
	{ WM_NCDESTROY,_T("WM_NCDESTROY") },
	{ WM_NCCALCSIZE,_T("WM_NCCALCSIZE") },
	{ WM_NCHITTEST,_T("WM_NCHITTEST") },
	{ WM_NCPAINT,_T("WM_NCPAINT") },
	{ WM_NCACTIVATE,_T("WM_NCACTIVATE") },
	{ WM_GETDLGCODE,_T("WM_GETDLGCODE") },
	{ WM_NCMOUSEMOVE,_T("WM_NCMOUSEMOVE") },
	{ WM_NCLBUTTONDOWN,_T("WM_NCLBUTTONDOWN") },
	{ WM_NCLBUTTONUP,_T("WM_NCLBUTTONUP") },
	{ WM_NCLBUTTONDBLCLK,_T("WM_NCLBUTTONDBLCLK") },
	{ WM_NCRBUTTONDOWN,_T("WM_NCRBUTTONDOWN") },
	{ WM_NCRBUTTONUP,_T("WM_NCRBUTTONUP") },
	{ WM_NCRBUTTONDBLCLK,_T("WM_NCRBUTTONDBLCLK") },
	{ WM_NCMBUTTONDOWN,_T("WM_NCMBUTTONDOWN") },
	{ WM_NCMBUTTONUP,_T("WM_NCMBUTTONUP") },
	{ WM_NCMBUTTONDBLCLK,_T("WM_NCMBUTTONDBLCLK") },
	{ WM_KEYDOWN,_T("WM_KEYDOWN") },
	{ WM_KEYUP,_T("WM_KEYUP") },
	{ WM_CHAR,_T("WM_CHAR") },
	{ WM_DEADCHAR,_T("WM_DEADCHAR") },
	{ WM_SYSKEYDOWN,_T("WM_SYSKEYDOWN") },
	{ WM_SYSKEYUP,_T("WM_SYSKEYUP") },
	{ WM_SYSCHAR,_T("WM_SYSCHAR") },
	{ WM_SYSDEADCHAR,_T("WM_SYSDEADCHAR") },
	{ WM_KEYDOWN,_T("WM_KEYDOWN") },
	{ WM_KEYUP,_T("WM_KEYUP") },
	{ WM_CHAR,_T("WM_CHAR") },
	{ WM_DEADCHAR,_T("WM_DEADCHAR") },
	{ WM_SYSKEYDOWN,_T("WM_SYSKEYDOWN") },
	{ WM_SYSKEYUP,_T("WM_SYSKEYUP") },
	{ WM_SYSCHAR,_T("WM_SYSCHAR") },
	{ WM_SYSDEADCHAR,_T("WM_SYSDEADCHAR") },
#if(WINVER >= 0x0400)
	{ WM_IME_STARTCOMPOSITION,_T("WM_IME_STARTCOMPOSITION") },
	{ WM_IME_ENDCOMPOSITION,_T("WM_IME_ENDCOMPOSITION") },
	{ WM_IME_COMPOSITION,_T("WM_IME_COMPOSITION") },
	{ WM_IME_KEYLAST,_T("WM_IME_KEYLAST") },
#endif
	{ WM_INITDIALOG,_T("WM_INITDIALOG") },
	{ WM_COMMAND,_T("WM_COMMAND") },
	{ WM_SYSCOMMAND,_T("WM_SYSCOMMAND") },
	{ WM_TIMER,_T("WM_TIMER") },
	{ WM_HSCROLL,_T("WM_HSCROLL") },
	{ WM_VSCROLL,_T("WM_VSCROLL") },
	{ WM_INITMENU,_T("WM_INITMENU") },
	{ WM_INITMENUPOPUP,_T("WM_INITMENUPOPUP") },
	{ WM_MENUSELECT,_T("WM_MENUSELECT") },
	{ WM_MENUCHAR,_T("WM_MENUCHAR") },
	{ WM_ENTERIDLE,_T("WM_ENTERIDLE") },
	{ WM_CTLCOLORMSGBOX,_T("WM_CTLCOLORMSGBOX") },
	{ WM_CTLCOLOREDIT,_T("WM_CTLCOLOREDIT") },
	{ WM_CTLCOLORLISTBOX,_T("WM_CTLCOLORLISTBOX") },
	{ WM_CTLCOLORBTN,_T("WM_CTLCOLORBTN") },
	{ WM_CTLCOLORDLG,_T("WM_CTLCOLORDLG") },
	{ WM_CTLCOLORSCROLLBAR,_T("WM_CTLCOLORSCROLLBAR") },
	{ WM_CTLCOLORSTATIC,_T("WM_CTLCOLORSTATIC") },
	{ WM_MOUSEMOVE,_T("WM_MOUSEMOVE") },
	{ WM_LBUTTONDOWN,_T("WM_LBUTTONDOWN") },
	{ WM_LBUTTONUP,_T("WM_LBUTTONUP") },
	{ WM_LBUTTONDBLCLK,_T("WM_LBUTTONDBLCLK") },
	{ WM_RBUTTONDOWN,_T("WM_RBUTTONDOWN") },
	{ WM_RBUTTONUP,_T("WM_RBUTTONUP") },
	{ WM_RBUTTONDBLCLK,_T("WM_RBUTTONDBLCLK") },
	{ WM_MBUTTONDOWN,_T("WM_MBUTTONDOWN") },
	{ WM_MBUTTONUP,_T("WM_MBUTTONUP") },
	{ WM_MBUTTONDBLCLK,_T("WM_MBUTTONDBLCLK") },
	{ WM_MOUSEMOVE,_T("WM_MOUSEMOVE") },
	{ WM_LBUTTONDOWN,_T("WM_LBUTTONDOWN") },
	{ WM_LBUTTONUP,_T("WM_LBUTTONUP") },
	{ WM_LBUTTONDBLCLK,_T("WM_LBUTTONDBLCLK") },
	{ WM_RBUTTONDOWN,_T("WM_RBUTTONDOWN") },
	{ WM_RBUTTONUP,_T("WM_RBUTTONUP") },
	{ WM_RBUTTONDBLCLK,_T("WM_RBUTTONDBLCLK") },
	{ WM_MBUTTONDOWN,_T("WM_MBUTTONDOWN") },
	{ WM_MBUTTONUP,_T("WM_MBUTTONUP") },
	{ WM_MBUTTONDBLCLK,_T("WM_MBUTTONDBLCLK") },
	{ WM_PARENTNOTIFY,_T("WM_PARENTNOTIFY") },
	{ WM_ENTERMENULOOP,_T("WM_ENTERMENULOOP") },
	{ WM_EXITMENULOOP,_T("WM_EXITMENULOOP") },
#if(WINVER >= 0x0400)
	{ WM_NEXTMENU,_T("WM_NEXTMENU") },
	{ WM_SIZING,_T("WM_SIZING") },
	{ WM_CAPTURECHANGED,_T("WM_CAPTURECHANGED") },
	{ WM_MOVING,_T("WM_MOVING") },
	{ WM_POWERBROADCAST,_T("WM_POWERBROADCAST") },
	{ WM_DEVICECHANGE,_T("WM_DEVICECHANGE") },
	{ WM_IME_SETCONTEXT,_T("WM_IME_SETCONTEXT") },
	{ WM_IME_NOTIFY,_T("WM_IME_NOTIFY") },
	{ WM_IME_CONTROL,_T("WM_IME_CONTROL") },
	{ WM_IME_COMPOSITIONFULL,_T("WM_IME_COMPOSITIONFULL") },
	{ WM_IME_SELECT,_T("WM_IME_SELECT") },
	{ WM_IME_CHAR,_T("WM_IME_CHAR") },
	{ WM_IME_KEYDOWN,_T("WM_IME_KEYDOWN") },
	{ WM_IME_KEYUP,_T("WM_IME_KEYUP") },
#endif
	{ WM_MDICREATE,_T("WM_MDICREATE") },
	{ WM_MDIDESTROY,_T("WM_MDIDESTROY") },
	{ WM_MDIACTIVATE,_T("WM_MDIACTIVATE") },
	{ WM_MDIRESTORE,_T("WM_MDIRESTORE") },
	{ WM_MDINEXT,_T("WM_MDINEXT") },
	{ WM_MDIMAXIMIZE,_T("WM_MDIMAXIMIZE") },
	{ WM_MDITILE,_T("WM_MDITILE") },
	{ WM_MDICASCADE,_T("WM_MDICASCADE") },
	{ WM_MDIICONARRANGE,_T("WM_MDIICONARRANGE") },
	{ WM_MDIGETACTIVE,_T("WM_MDIGETACTIVE") },
	{ WM_MDISETMENU,_T("WM_MDISETMENU") },
	{ WM_ENTERSIZEMOVE,_T("WM_ENTERSIZEMOVE") },
	{ WM_EXITSIZEMOVE,_T("WM_EXITSIZEMOVE") },
	{ WM_DROPFILES,_T("WM_DROPFILES") },
	{ WM_MDIREFRESHMENU,_T("WM_MDIREFRESHMENU") },
	{ WM_CUT,_T("WM_CUT") },
	{ WM_COPY,_T("WM_COPY") },
	{ WM_PASTE,_T("WM_PASTE") },
	{ WM_CLEAR,_T("WM_CLEAR") },
	{ WM_UNDO,_T("WM_UNDO") },
	{ WM_RENDERFORMAT,_T("WM_RENDERFORMAT") },
	{ WM_RENDERALLFORMATS,_T("WM_RENDERALLFORMATS") },
	{ WM_DESTROYCLIPBOARD,_T("WM_DESTROYCLIPBOARD") },
	{ WM_DRAWCLIPBOARD,_T("WM_DRAWCLIPBOARD") },
	{ WM_PAINTCLIPBOARD,_T("WM_PAINTCLIPBOARD") },
	{ WM_VSCROLLCLIPBOARD,_T("WM_VSCROLLCLIPBOARD") },
	{ WM_SIZECLIPBOARD,_T("WM_SIZECLIPBOARD") },
	{ WM_ASKCBFORMATNAME,_T("WM_ASKCBFORMATNAME") },
	{ WM_CHANGECBCHAIN,_T("WM_CHANGECBCHAIN") },
	{ WM_HSCROLLCLIPBOARD,_T("WM_HSCROLLCLIPBOARD") },
	{ WM_QUERYNEWPALETTE,_T("WM_QUERYNEWPALETTE") },
	{ WM_PALETTEISCHANGING,_T("WM_PALETTEISCHANGING") },
	{ WM_PALETTECHANGED,_T("WM_PALETTECHANGED") },
	{ WM_HOTKEY,_T("WM_HOTKEY") },
#if(WINVER >= 0x0400)
	{ WM_PRINT,_T("WM_PRINT") },
	{ WM_PRINTCLIENT,_T("WM_PRINTCLIENT") },
#endif
	// Below are MFC messages
	{ WM_QUERYAFXWNDPROC,_T("*WM_QUERYAFXWNDPROC") },
	{ WM_SIZEPARENT,_T("*WM_SIZEPARENT") },
	{ WM_SETMESSAGESTRING,_T("*WM_SETMESSAGESTRING") },
	{ WM_IDLEUPDATECMDUI,_T("*WM_IDLEUPDATECMDUI") },
	{ WM_INITIALUPDATE,_T("*WM_INITIALUPDATE") },
	{ WM_COMMANDHELP,_T("*WM_COMMANDHELP") },
	{ WM_HELPHITTEST,_T("*WM_HELPHITTEST") },
	{ WM_EXITHELPMODE,_T("*WM_EXITHELPMODE") },
	{ WM_RECALCPARENT,_T("*WM_RECALCPARENT") },
	{ WM_SIZECHILD,_T("*WM_SIZECHILD") },
	{ WM_KICKIDLE,_T("*WM_KICKIDLE") },
	{ WM_QUERYCENTERWND,_T("*WM_QUERYCENTERWND") },
	{ WM_DISABLEMODAL,_T("*WM_DISABLEMODAL") },
	{ WM_FLOATSTATUS,_T("*WM_FLOATSTATUS") },
	{ WM_ACTIVATETOPLEVEL,_T("*WM_ACTIVATETOPLEVEL") },
	{ WM_QUERY3DCONTROLS,_T("*WM_QUERY3DCONTROLS") },
	{ WM_SOCKET_NOTIFY,_T("*WM_SOCKET_NOTIFY") },
	{ WM_SOCKET_DEAD,_T("*WM_SOCKET_DEAD") },
	{ WM_POPMESSAGESTRING,_T("*WM_POPMESSAGESTRING") },
	{ WM_OCC_LOADFROMSTREAM,_T("*WM_OCC_LOADFROMSTREAM") },
	{ WM_OCC_LOADFROMSTORAGE,_T("*WM_OCC_LOADFROMSTORAGE") },
	{ WM_OCC_INITNEW,_T("*WM_OCC_INITNEW") },
	{ WM_QUEUE_SENTINEL,_T("*WM_QUEUE_SENTINEL") },
	{ 0,NULL }
};

////////////////
// This class is basically just an array of 1024 strings,
// the names of each WM_ message. Constructor initializes it.
//
class CWndMsgMap {
	static LPCTSTR Names[];				// array of WM_ message names
public:
	CWndMsgMap();							// constructor initializes them
	CString GetMsgName(UINT msg);		// get name of message
};
LPCTSTR CWndMsgMap::Names[WM_USER];	// name of each WM_ message

//////////////////
// Initialize array from sparse data
//
CWndMsgMap::CWndMsgMap()
{
	// copy sparse MsgData into table
	memset(Names, 0, sizeof(Names));
	for (int i=0; MsgData[i].msg; i++)		
		Names[MsgData[i].msg] = MsgData[i].name;
}

////////////////
// Get the name of a WM_ message
//
CString CWndMsgMap::GetMsgName(UINT msg)
{
	CString name;
	if (msg>=WM_USER)
		name.Format("WM_USER+%d", msg-WM_USER);
	else if (Names[msg])
		name = Names[msg];
	else
		name.Format("0x%04x", msg);
	return name;
}

//////////////////
// Get name of WM_ message.
//
CString sDbgName(UINT uMsg)
{
	static CWndMsgMap wndMsgMap; // instantiate 1st time called
	return wndMsgMap.GetMsgName(uMsg);
}

#ifdef REFIID

// Most apps don't need to use DbgName(REFIID)
// Apps that do can set this static global to a table of
// DBGINTERFACENAME's it wants to TRACE with DbgName(REFIID)
//
DBGINTERFACENAME* _pDbgInterfaceNames = NULL;

//////////////////
// Get OLE interface name.
//
CString sDbgName(REFIID iid)
{
	if (_pDbgInterfaceNames) {
		for (int i=0; _pDbgInterfaceNames[i].name; i++) {
			if (memcmp(_pDbgInterfaceNames[i].piid, &iid, sizeof(IID))==0)
				return _pDbgInterfaceNames[i].name;
		}
	}
	static CString s;
	s.Format("{%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x}",
		iid.Data1, iid.Data2, iid.Data3,
		iid.Data4[0], iid.Data4[1], iid.Data4[2], iid.Data4[3],
		iid.Data4[4], iid.Data4[5], iid.Data4[6], iid.Data4[7]);
	return s;
}

#endif // REFIID

#endif // _DEBUG
