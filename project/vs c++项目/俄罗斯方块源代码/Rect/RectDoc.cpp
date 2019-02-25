// RectDoc.cpp : implementation of the CRectDoc class
//

#include "stdafx.h"
#include "Rect.h"

#include "RectDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRectDoc

IMPLEMENT_DYNCREATE(CRectDoc, CDocument)

BEGIN_MESSAGE_MAP(CRectDoc, CDocument)
	//{{AFX_MSG_MAP(CRectDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRectDoc construction/destruction

CRectDoc::CRectDoc()
{
	// TODO: add one-time construction code here

}

CRectDoc::~CRectDoc()
{
}

BOOL CRectDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CRectDoc serialization

void CRectDoc::Serialize(CArchive& ar)
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
// CRectDoc diagnostics

#ifdef _DEBUG
void CRectDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRectDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRectDoc commands
