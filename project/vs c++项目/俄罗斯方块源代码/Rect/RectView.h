// RectView.h : interface of the CRectView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECTVIEW_H__54F67C8D_EFFA_11D5_9B6C_959406F6741C__INCLUDED_)
#define AFX_RECTVIEW_H__54F67C8D_EFFA_11D5_9B6C_959406F6741C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRectView : public CView
{
public:
	bool begin;					//��¼�Ƿ� --��ʼ״̬
	bool stop;					//��¼�Ƿ� --��ͣ״̬

	bool game_begin;			//��¼�Ƿ� --��ʼ״̬
	bool game_stop;				//��¼�Ƿ� --��ͣ״̬
	bool game_end;				//��¼�Ƿ� --����״̬


	bool game_music;			//��¼�Ƿ����ڲ�������
	bool game_hasGrid;			//��¼�Ƿ�����

	int game_level;				//��¼��Ϸ����
	int game_speed;				//��¼/��Ϸ�ٶ�
	void Print(int level);		//��ʾ��Ϸ����
	void SetLevel(int score);	//������������Ϸ����


protected: // create from serialization only
	CRectView();
	virtual ~CRectView();
	DECLARE_DYNCREATE(CRectView)

// Attributes
public:
	CRectDoc* GetDocument();

public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRectView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL


#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRectView)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMganBigne();
	afx_msg void OnGameExit();
	afx_msg void OnUpdateGameBigrn(CCmdUI* pCmdUI);
	afx_msg void OnGameStop();
	afx_msg void OnUpdateGameStop(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGameExit(CCmdUI* pCmdUI);
	afx_msg void OnGameEnd();
	afx_msg void OnUpdateGameEnd(CCmdUI* pCmdUI);
	afx_msg void OnSetGrade1();
	afx_msg void OnUpdateSetGrade1(CCmdUI* pCmdUI);
	afx_msg void OnSetGrade2();
	afx_msg void OnUpdateSetGrade2(CCmdUI* pCmdUI);
	afx_msg void OnSetGrade3();
	afx_msg void OnUpdateSetGrade3(CCmdUI* pCmdUI);
	afx_msg void OnSetGrid();
	afx_msg void OnUpdateSetGrid(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHelpMinyan(CCmdUI* pCmdUI);
	afx_msg void OnSetGrade0();
	afx_msg void OnUpdateSetGrade0(CCmdUI* pCmdUI);
	afx_msg void OnSetGrade4();
	afx_msg void OnUpdateSetGrade4(CCmdUI* pCmdUI);
	afx_msg void OnSetMusic();
	afx_msg void OnUpdateSetMusic(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in RectView.cpp
inline CRectDoc* CRectView::GetDocument()
   { return (CRectDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECTVIEW_H__54F67C8D_EFFA_11D5_9B6C_959406F6741C__INCLUDED_)
