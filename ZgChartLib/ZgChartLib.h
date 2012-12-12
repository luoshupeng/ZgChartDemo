#ifndef ZGCHARTLIB_H
#define ZGCHARTLIB_H

//ZgChartLib Copyright 2004-2005 ZhuGang
//��  ��:������ʾ��
//ͷ�ļ�:ZgChartLib.h
//���ļ�:ZgChartLib.lib
//////////////////////////////////////////////////////////////////////////
//��  ��:����mschart
//˵  ��1:��������Ϊʱ��ֵ
//˵  ��2:��������Ϊ��ֵ(float)

//������ϸ˵������
//1:ʱ����������ݵ���ʾ
//2:���10������ͬʱ��ʾ
//3:������Ϣ���浽λͼ�ļ�
//4:������Ϣ��ӡ����Ҫ�����ӡDC�������ӳ������Ҹ�������ϸ�Ĵ���
//5:������ʾʱ��̬�����Ƿ���ʾ(����������ͼ��)
//6:���ߵ�ǰ���λ�����ݰ�͸����ʾ(Windows2000����֧��)
//7:����������ֵ��ʾ
//8:���߶�̬������ɫ���߿��Ҽ��������ͼ�������뱣���Ի�����ԴIDD_DIALOG_LINE_SET,������ʹ�ã�

//һЩ˵��:����������װ�ɾ�̬Lib,�Ի�����Դ�Ļ�ȡ�������⣬���˻�û���ҵ���������������ʹ��DLL��û������/
//�������֪����λ�ȡ��̬Lib�е���Դ������лл�̽���

//////////////////////////////////////////////////////////////////////////
//��ҿ������ʹ�ñ����ӿ⣬���뱣����Щ˵������
//���������BUG��������ϵ��sonystone@tom.com, sonystone@163.com
//������ҪC++Դ���룬���뱾����ϵ
//��ο����ӳ���
//�벻Ҫ�޸����´��룬������ִ���

//////////////////////////////////////////////////////////////////////////
class CZgMemDC : public CDC 
{
	CZgMemDC(CDC* pDC, const CRect* pRect = NULL);
	~CZgMemDC();
};

//////////////////////////////////////////////////////////////////////////
class CZgBitmap : public CBitmap  
{
public:
	CZgBitmap();
	virtual ~CZgBitmap();
};

//////////////////////////////////////////////////////////////////////////
// CColourPopup messages
#define CPN_SELCHANGE        WM_USER + 1001        // Colour Picker Selection change
#define CPN_DROPDOWN         WM_USER + 1002        // Colour Picker drop down
#define CPN_CLOSEUP          WM_USER + 1003        // Colour Picker close up
#define CPN_SELENDOK         WM_USER + 1004        // Colour Picker end OK
#define CPN_SELENDCANCEL     WM_USER + 1005        // Colour Picker end (cancelled)

// forward declaration
class CColourPicker;

// To hold the colours and their names
typedef struct {
    COLORREF crColour;
    TCHAR    *szName;
} ColourTableEntry;

/////////////////////////////////////////////////////////////////////////////
// CColourPopup window

class CColourPopup : public CWnd
{
// Construction
public:
    CColourPopup();
    CColourPopup(CPoint p, COLORREF crColour, COLORREF crDefaultColour, CWnd* pParentWnd,
                 LPCTSTR szDefaultText = NULL, LPCTSTR szCustomText = NULL);
    void Initialise();

	void SetDefaultColor(COLORREF crColour) { m_crDefaultColour = crColour; }


// Attributes
public:

// Operations
public:
    BOOL Create(CPoint p, COLORREF crColour, CWnd* pParentWnd, 
                LPCTSTR szDefaultText = NULL, LPCTSTR szCustomText = NULL);

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CColourPopup)
    public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    //}}AFX_VIRTUAL

// Implementation
public:
	void SetDefaultColour(COLORREF crDefaultColour);
    virtual ~CColourPopup();

protected:
    BOOL GetCellRect(int nIndex, const LPRECT& rect);
    void FindCellFromColour(COLORREF crColour);
    void SetWindowSize();
    void CreateToolTips();
    void ChangeSelection(int nIndex);
    void EndSelection(int nMessage);
    void DrawCell(CDC* pDC, int nIndex);

    COLORREF GetColour(int nIndex)              { return m_crColours[nIndex].crColour; }
    LPCTSTR GetColourName(int nIndex)           { return m_crColours[nIndex].szName; }
    int  GetIndex(int row, int col) const;
    int  GetRow(int nIndex) const;
    int  GetColumn(int nIndex) const;

// protected attributes
protected:
    static ColourTableEntry m_crColours[];
    int            m_nNumColours;
    int            m_nNumColumns, m_nNumRows;
    int            m_nBoxSize, m_nMargin;
    int            m_nCurrentSel;
    int            m_nChosenColourSel;
    CString        m_strDefaultText;
    CString        m_strCustomText;
    CRect          m_CustomTextRect, m_DefaultTextRect, m_WindowRect;
    CFont          m_Font;
    CPalette       m_Palette;
    COLORREF       m_crInitialColour, m_crColour;
	COLORREF	   m_crDefaultColour;
    CToolTipCtrl   m_ToolTip;
    CWnd*          m_pParent;


    // Generated message map functions
protected:
    //{{AFX_MSG(CColourPopup)
    afx_msg void OnNcDestroy();
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnPaint();
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg BOOL OnQueryNewPalette();
    afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnActivateApp(BOOL bActive, HTASK hTask);
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


//////////////////////////////////////////////////////////////////////////
void AFXAPI DDX_ColourPicker(CDataExchange *pDX, int nIDC, COLORREF& crColour);

/////////////////////////////////////////////////////////////////////////////
// CColourPicker window

#define CP_MODE_TEXT 1  // edit text colour
#define CP_MODE_BK   2  // edit background colour (default)

class CColourPicker : public CButton
{
// Construction
public:
    CColourPicker();
    DECLARE_DYNCREATE(CColourPicker);

// Attributes
public:
    COLORREF GetColour();
    void     SetColour(COLORREF crColour); 

    void     SetDefaultText(LPCTSTR szDefaultText);
    void     SetCustomText(LPCTSTR szCustomText);

    void     SetTrackSelection(BOOL bTracking = TRUE)  { m_bTrackSelection = bTracking; }
    BOOL     GetTrackSelection()                       { return m_bTrackSelection; }

    void     SetSelectionMode(UINT nMode)              { m_nSelectionMode = nMode; }
    UINT     GetSelectionMode()                        { return m_nSelectionMode; };

    void     SetBkColour(COLORREF crColourBk);
    COLORREF GetBkColour()                             { return m_crColourBk; }
    
    void     SetTextColour(COLORREF crColourText);
    COLORREF GetTextColour()                           { return m_crColourText;}

	//void	 SetDefaultColour(COLORREF crColour) {  m_crColourBk = m_crColourText = crColour; }
	void	 SetDefaultColour(COLORREF crColour) {  m_crDefaultBkColour = crColour; }


// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CColourPicker)
    public:
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
    protected:
    virtual void PreSubclassWindow();
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CColourPicker();

protected:
    void SetWindowSize();

// protected attributes
protected:
    BOOL     m_bActive,                // Is the dropdown active?
             m_bTrackSelection;        // track colour changes?
    COLORREF m_crColourBk;
    COLORREF m_crColourText;
    UINT     m_nSelectionMode;
    CRect    m_ArrowRect;
    CString  m_strDefaultText;
    CString  m_strCustomText;
	COLORREF m_crDefaultColour;
	COLORREF m_crDefaultBkColour;

    // Generated message map functions
protected:
    //{{AFX_MSG(CColourPicker)
    afx_msg BOOL OnClicked();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    //}}AFX_MSG
    afx_msg LONG OnSelEndOK(UINT lParam, LONG wParam);
    afx_msg LONG OnSelEndCancel(UINT lParam, LONG wParam);
    afx_msg LONG OnSelChange(UINT lParam, LONG wParam);

    DECLARE_MESSAGE_MAP()
};



//////////////////////////////////////////////////////////////////////////
typedef struct STRU_TIPSHOW_DATA
{
	CString		strTipsText;			//��ʾ�ı�
	COLORREF	crTipsColor;			//��ʾ�ı���ɫ
}TipShowData;
//////////////////////////////////////////////////////////////////////////
class CZgChartTips  
{
public:
	CZgChartTips();
	virtual ~CZgChartTips();

protected:
	void DrawTips(CDC *pDC, CRect &rcDraw, TipShowData *pData);
	void DrawAllTips(CDC *pDC, CRect &rcDraw);
	BOOL MakeChartTips(CDC *pDC);
	CZgBitmap m_BitmapTips;
	CSize m_szMaxText;
	CPtrList m_TipsList;
	CSize m_szBitmap;
	CFont m_FontText;
};

//////////////////////////////////////////////////////////////////////////
class CZgChartTipsWnd : public CWnd
{
	DECLARE_DYNAMIC(CZgChartTipsWnd);
// Construction
public:
	CZgChartTipsWnd();

// Attributes
public:
	CZgChartTips *mp_ChartTips;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZgChartTipsWnd)
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL CreateTipsWnd(CRect rect, CWnd *pParent);
	virtual ~CZgChartTipsWnd();

	// Generated message map functions
protected:
	CWnd *mp_Parent;
	BOOL SetTransparent(HWND hWnd, COLORREF crKey, BYTE bAlpha, DWORD dwFlags);
	HMODULE	m_hUserDll ;		//DLL
	//{{AFX_MSG(CZgChartTipsWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

typedef struct STRU_CUTLINE_DATA
{
	char		szCutlineName[40];		//ͼ������
	COLORREF	crCutlineColor;			//ͼ����ɫ
	UINT		nLineWidth;				//���߿��
	CRect		rcPos;					//ͼ��λ��
	BOOL		bStatus;				//ͼ��״̬
}CutlineData;

//////////////////////////////////////////////////////////////////////////
class CZgChartCutline
{
// Construction
public:
	CZgChartCutline();

public:
	void UpdateCutlinePara(COLORREF crColor, UINT nLineWidth, int nIndex);
	BOOL GetCutlineStatusByIndex(int nIndex);
	void ReverseStatus(int nIndex);
	BOOL GetCutlineRectByIndex(CRect &rcPos, int nIndex);
	BOOL GetCutlineColorInfoByIndex(COLORREF &crColor, UINT &nLineWidth, int nIndex);
	BOOL GetCutlineInfoByIndex(CString &strName, COLORREF &crColor, int nIndex);
	void ShowChartCutline(CDC *pDC, CRect &rcDraw);
	BOOL AddChartCutline(char szName[], COLORREF crColor, UINT nLineWidth=2, BOOL bClearData=FALSE);
	void EmptyData();
	virtual ~CZgChartCutline();

protected:
	void DrawCutline(CDC *pDC, CRect &rcDraw, CutlineData *pData);
	void DrawAllCutline(CDC *pDC, CRect &rcClient);
	CPtrList m_CutlineList;
};


//////////////////////////////////////////////////////////////////////////
#define IDD_DIALOG_LINE_SET             101
#define IDC_COMBO_LINEWIDTH             1038
#define IDC_BUTTON_LINECOLOR            1039

class CZgChartLineSetDlg : public CDialog
{
// Construction
public:
	CZgChartLineSetDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CZgChartLineSetDlg)
	enum { IDD = IDD_DIALOG_LINE_SET };
	CColourPicker	m_LineColor;
	int		mi_LineWidth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZgChartLineSetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CZgChartLineSetDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//////////////////////////////////////////////////////////////////////////
#define MAX_CURVE_COUNT	10		//�����������
typedef struct STRU_CHART_DATA
{
	int			nValueTime;		//ʱ���
	float		fValue;			//ֵ
	BOOL		bValid;			//�Ƿ���Ч
}ChartData;


class CZgChartView : public CWnd
{
// Construction
public:
	CZgChartView();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZgChartView)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	//����ʱ���������Բ����ã����ڻ�ȡ��ֵ�����һЩС����
	void SetTimeSpin(int nTimeSpin);

	//���浱ǰ���ߵ�ָ��λͼ�ļ�
	BOOL SaveChartToFile(CString &strFileName);

	//��ӡ��ǰ����
	void PrintChart(CDC *pDC);

	//ǿ�����ص�ǰ��ʾ����
	void HideTips();

	//�������߱����ı�
	void SetTitleText(CString &strTitle);

	//�������������Ϣ
	BOOL AddChartData(int nIndex, int nTime, float fValue, BOOL bValid=TRUE);

	//������������ķ�Χ
	void SetYValue(int nMin, int nMax);

	//�����������
	BOOL AddChartCutline(char szName[], COLORREF crColor, UINT nLineWidth=2, BOOL bClearData=FALSE);
	
	//��������,���ʱ��ı���������ܹ���24����
	void SetXDate(int nStart, int nStop);

	//����������ʾ����
	BOOL CreateChartView(CWnd *pParentWnd, CRect &rect);
	virtual ~CZgChartView();

	// Generated message map functions
protected:
	CZgChartCutline m_ChartCutline;		//����ͼ��
	CZgChartTips	m_ChartTips;		//������ʾ
	
	int mi_SpinX;			//X��ȷִ�С
	int mi_SpinY;			//Y��ȷִ�С

	int mi_MarginTop;		//���߶������	
	int mi_MarginBottom;	//���ߵײ����
	int mi_MarginLeft;		//������߼��
	int mi_MarginRight;		//�����ұ߼��

	int mi_SpinWidth;		//X����
	int mi_SpinHeight;		//Y��߶�

	COLORREF m_crTitleText;	//�����ı���ɫ
	CString m_strTitleText;	//�����ı�
	UINT	mi_TitleAlign;	//�����ı��������ͣ����У���

	COLORREF m_crDate;		//��ʾ��ʾ��ʱ�����ɫ
	COLORREF m_crBackground;//���߱�����ɫ
	COLORREF m_crScaleText;	//�̶��ı���ɫ
	COLORREF m_crLinePoint;	//������ɫ

	UINT mi_TimerMove;		//��ʱ��

	CPoint m_ptSave;		//���걣���

	int	mi_MinX;			//X����Сֵ
	int mi_MaxX;			//X�����ֵ

	int mi_MinY;			//Y����Сֵ
	int mi_MaxY;			//Y�����ֵ

	int mi_DayCount;		//����

	CFont m_FontText;		//�ı�����
	CFont m_FontTitle;		//������������

	CPen m_PenCoordinate;	//������
	CPen m_PenArrow;		//�������ͷ
	CPen m_PenSpinLine;		//������ָ���
	CPen m_PenPosLine;		//����������еĶ�λ��

	CRect m_rcClient;		//�����ͻ�����ONSIZE�¼��и���
	CRect m_rcCurve;		//����

	int	mi_CurveCount;		//��������

	BOOL mi_DrawLineSmooth;	//�Ƿ�ʹ��Bezier��ƽ������
	BOOL mi_TipsWithMouse;	//��ʾ��ʾ�Ƿ������
	BOOL mi_DrawLineVertical;//��Bezier��ƽ������ʱ���Ƿ����ֱ��ͼ��ʽ

	CPtrList m_DataList[MAX_CURVE_COUNT];		//���ʮ�����ߵ����ݱ����

	int mi_TimeSpin;		//����ʱ����

protected:
	int mi_CurDataIndexSave;
	CZgChartTipsWnd m_ChartTipsWnd;
	BOOL SaveBitmapToFile(HBITMAP hBitmap , CString &strFileName);
	void DrawYFloatTextFromValue(CDC *pDC, CPoint ptText, float fValue);
	void DrawCutline(CDC* pDC, CRect &rcClient);
	void DrawCrossLine(CDC *pDC);
	void DrawChartTips(CDC *pDC);
	int GetDateStringByX(CString &strDate, int nChartIndex);
	void DatePointToChartPoint(CPoint &ptChart, int nTime, float fValue);
	void DrawSingleCurveSmooth(CDC *pDC, int nIndex, CRect &rcDraw);
	void DrawSingleCurveNoSmooth(CDC *pDC, int nIndex, CRect &rcDraw);
	void GetXStringByPos(CString &strText);
	float GetYValueByPos();
	void DrawFloatTextFromValue(CDC *pDC, CPoint ptText, float fValue);
	void DrawDateTextFromValue(CDC *pDC, CPoint ptText, int nValue);
	void DrawFloatTextFromValue(CDC *pDC, CPoint ptText, int nValue);
	void DrawChartTitle(CDC *pDC, CRect &rcDraw, BOOL bPrint=FALSE);
	void DrawCurve(CDC *pDC, CRect &rcDraw);
	void DrawCoordinate(CDC *pDC, CRect &rcDraw);
	//{{AFX_MSG(CZgChartView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif

