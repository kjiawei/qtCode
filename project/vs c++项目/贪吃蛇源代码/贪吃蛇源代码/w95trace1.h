/*
    declarations for Win95 tracing facility
*/

//      TRACEFN("%s:OnPaint()\n",DbgName(this));
//      TRACEFN("%s:OnPaint()\n",DbgName(WM_PAINT));

#ifndef __TRACEW95__
#define __TRACEW95__

#ifdef _DEBUG

void ClearDebugWindow(char *str=0, BOOL bClean=TRUE); /* pyt */

// redefine all the MFC macros to point to us

#undef  TRACE
#define TRACE   OutputDebugStringW95

#undef  TRACE0
#define TRACE0   OutputDebugStringW95

#undef  TRACE1
#define TRACE1   OutputDebugStringW95

#undef  TRACE2
#define TRACE2   OutputDebugStringW95

#undef  TRACE3
#define TRACE3   OutputDebugStringW95

// redefine OutputDebugString so that it works with 
// API calls
#undef OutputDebugString
#define OutputDebugString   OutputDebugStringW95


// function declarations
void OutputDebugStringW95( LPCTSTR lpOutputString, ... );


//////////////////
// Implements TRACEFN macro.
// Don't ever use directly, just use TRACEFN
//
class CTraceFn {
private:
	static int	nIndent;	// current indent level
	friend void AFX_CDECL AfxTrace(LPCTSTR lpszFormat, ...);
    friend void OutputDebugStringW95(LPCTSTR lpOutputString, ...);
public:
	CTraceFn()  { nIndent++; }
	~CTraceFn() { nIndent--; }
};

// NOTE: YOU MUST NOT USE TRACEFN IN A ONE-LINE IF STATEMENT!
// This will fail:
//
// if (foo)
//    TRACEFN(...)
//
// Instead, you must enclose the TRACE in squiggle-brackets
//
// if (foo) {
//		TRACEFN(...)
// }
//
#define TRACEFN CTraceFn __fooble; TRACE

// Goodies to get names of things.
//
extern CString sDbgName(CWnd* pWnd); // get name of window
extern CString sDbgName(UINT uMsg);	 // get name of WM_ message

#ifdef REFIID

struct DBGINTERFACENAME {
	const IID* piid;	// ptr to GUID
	LPCSTR name;		// human-readable name of interface
};

// Change this to whatever interfaces you want to track
// Default is none
//
extern DBGINTERFACENAME* _pDbgInterfaceNames; 

extern CString sDbgName(REFIID iid);	// get name of COM interface

#endif // REFIID


// Macro casts to LPCTSTR for use with TRACE/printf/CString::Format
//
#define DbgName(x) (LPCTSTR)sDbgName(x)

#else // Not _DEBUG

#define sDbgName(x)	CString()
#define TRACEFN TRACE

#endif  // _DEBUG

#endif  //__TRACEW95__
